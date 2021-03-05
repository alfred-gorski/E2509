/**
 * @file 				U_DrvSPI.c
 * @brief  	    Enable the information Trasmitionvia SPI protocol
 * @details     Inilization and transmation funcions as well as the Enable/Latch function of the SPI protocol 
 * @version 		1.0.0
 */


#include <HW_GPIO.h>
#include <HW_SPI.h>
#include <HW_RCC.h>
#include <Compiler.h>


#include <U_DrvSPI.h>
#include <U_Queue.h>
#include <U_GPIOConfig.h>


/// \brief Inlization of the two SPI
void SPIInit(SPIHandle* hSPI, Color color){
	_SPIGPIOs gpios;
	
	
	
	/*
	Name of the following GPIO for SPI:
		latch;
		clock;
		input;
		output;
	_GPIOConfig outEn;
	
	*/
	const _SPIGPIOs SPIGPIOsGn = {
		{&GPIOA, 4},
		{&GPIOA, 5},
		{&GPIOA, 6},
		{&GPIOA, 7},
		{&GPIOC, 4},
	};

	const _SPIGPIOs SPIGPIOsRd = {
		{&GPIOB, 12},
		{&GPIOB, 13},
		{&GPIOB, 14},
		{&GPIOB, 15},
		{&GPIOC, 6},
	};
	
	switch(color){
		case Gn:
			hSPI->instance = &SPI1;
			hSPI->gpios = SPIGPIOsGn;
			PeripheryEnable(RCC_SPI1);
			hSPI->color = Gn;
			break;
		case Rd:
			hSPI->instance = &SPI2;
			hSPI->gpios = SPIGPIOsRd;
			PeripheryEnable(RCC_SPI2);
			hSPI->color = Rd;
			break;
	}
	
	gpios = hSPI->gpios;
	
	//configurate the used GPIO's input/output
	
	GPIOConfig(gpios.latch,	GPIO_O_STD_PP_02MHZ);
	GPIOConfig(gpios.clock,	GPIO_O_ALT_PP_02MHZ);
	GPIOConfig(gpios.input,	GPIO_I_FLOATING);
	GPIOConfig(gpios.output,	GPIO_O_ALT_PP_02MHZ);
	GPIOConfig(gpios.outEn,	GPIO_O_STD_PP_02MHZ);
	
	
	//configurate the SPI registor
	hSPI->instance->CR1 |= 
							(BaudRateScaler_8 << INDX_SPI_CR1_BR)		// baudrate f_pclk/8
							| MASK_SPI_CR1_CPOL 										// second clock transition is the first data capture edge
							| MASK_SPI_CR1_SSM
							| MASK_SPI_CR1_SSI
							| MASK_SPI_CR1_MSTR;										// master configuration

	hSPI->instance->CR1 |= MASK_SPI_CR1_SPE;							// Enable
	
	
}




/// \brief send a message of given data via the chosen SPI
int SPIEmit(SPIHandle *hSPI,uint32_t data){
	uint8_t TxCount = 0;
	uint8_t TimeOutCount = 0;
	uint8_t pick = 0;
	
	// change the status of given SPI
	hSPI->status = BUSY;
	
	while(TxCount < 4 && TimeOutCount < TIMEOUT_THRESHOLD ){
		if((hSPI->instance->SR&MASK_SPI_SR_TXE)==MASK_SPI_SR_TXE){
			pick = data & SIZE_8_MASK;
			//move on to the next part of data by changing the pointer
			data = data >> 8;
			hSPI->instance->DR=pick;
			TxCount++;
		}else{
			
			// Time out check
			TimeOutCount++;
			if(TimeOutCount==TIMEOUT_THRESHOLD){
				hSPI->status=ERROR;	
			}
		}
	}
	
	
	//Error check
	if(hSPI->status==BUSY){
		hSPI->status=OK;
		return SUCCEED_SEND;
	}else{
		return ERROR_SEND;
	}
}




//Latch the given data 
void SPILatch(SPIHandle *hSPI){
	_GPIOConfig latch = hSPI->gpios.latch;
	setGPIOPin(latch);
	resetGPIOPin(latch);
}


/// \brief output enable
void SPIOutEn(SPIHandle *hSPI){
	_GPIOConfig outEn = hSPI->gpios.outEn;
	setGPIOPin(outEn);
	
}

void SPIOutEnOff(SPIHandle *hSPI){
	_GPIOConfig outEn = hSPI->gpios.outEn;
	resetGPIOPin(outEn);
}

