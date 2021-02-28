
#include <HW_GPIO.h>
#include <HW_SPI.h>
#include <HW_RCC.h>
#include <Compiler.h>


#include <U_DrvSPI.h>
#include <U_Queue.h>
#include <U_GPIOConfig.h>








SPIHandle SPIInit(Color color){
	SPIHandle hSPI;
	_SPIGPIOs gpios;
	
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
			hSPI.instance = &SPI1;
			hSPI.gpios =SPIGPIOsGn;
			PeripheryEnable(RCC_SPI1);
			break;
		case Rd:
			hSPI.instance = &SPI2;
			hSPI.gpios = SPIGPIOsRd;
			PeripheryEnable(RCC_SPI2);
			break;
	}
	
	gpios = hSPI.gpios;
	
	GPIOConfig(gpios.latch,	GPIO_O_STD_PP_02MHZ);
	GPIOConfig(gpios.clock,	GPIO_O_ALT_PP_02MHZ);
	GPIOConfig(gpios.input,	GPIO_I_FLOATING);
	GPIOConfig(gpios.output,	GPIO_O_ALT_PP_02MHZ);
	GPIOConfig(gpios.outEn,	GPIO_O_STD_PP_02MHZ);
	
	hSPI.instance->CR1 |= 
							(BaudRateScaler_8 << INDX_SPI_CR1_BR)		// baudrate f_pclk/8
							| MASK_SPI_CR1_CPOL 										// second clock transition is the first data capture edge
							| MASK_SPI_CR1_SSM
							| MASK_SPI_CR1_SSI
							| MASK_SPI_CR1_MSTR;										// master configuration

	hSPI.instance->CR1 |= MASK_SPI_CR1_SPE;							// Enable
	
	return hSPI;
	
}



int SPIEmit(SPIHandle *hSPI,uint32_t data){
	BYTE TxCount = 0;
	BYTE TimeOutCount = 0;
	BYTE pick = 0;
	
	hSPI->status = BUSY;
	while(TxCount < 4 && TimeOutCount < TIMEOUT_THRESHOLD ){
		if((hSPI->instance->SR&MASK_SPI_SR_TXE)==MASK_SPI_SR_TXE){
			pick = data & SIZE_8_MASK;
			data = data >> 8;
			hSPI->instance->DR=pick;
			TxCount++;
		}else{
			TimeOutCount++;
			if(TimeOutCount==TIMEOUT_THRESHOLD){
				hSPI->status=ERROR;	
			}
		}
	}
	if(hSPI->status==BUSY){
		hSPI->status=OK;
		return SUCCEED_SEND;
	}else{
		return ERROR_SEND;
	}
}



void SPILatch(SPIHandle *hSPI){
	_GPIOConfig latch = hSPI->gpios.latch;
	resetGPIOPin(latch);
	//latch.gpio->BSRR|= (1<<latch.pin);
}



void SPIOutEn(SPIHandle *hSPI){
	_GPIOConfig outEn = hSPI->gpios.outEn;
	setGPIOPin(outEn);
	//outEn.gpio->BSRR|= (1<<outEn.pin);
}

void SPIOutEnOff(SPIHandle *hSPI){
	_GPIOConfig outEn = hSPI->gpios.outEn;
	resetGPIOPin(outEn);
	//outEn.gpio->BSRR|= (1<<outEn.pin);
}


/*

void SPIGPIOConfig(_GPIOConfig gpioconfig, uint8_t value){
	ConfigureGPIO(gpioconfig.gpio,gpioconfig.pin,value);
}

*/
