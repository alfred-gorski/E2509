#include <U_DrvSPI.h>
#include <HW_GPIO.h>
#include <HW_SPI.h>
#include <HW_RCC.h>
#include <Compiler.h>

#include <U_Queue.h>



SPIHandle hSPIGn;
SPIHandle hSPIRd;


void SPIGPIOConfig(_GPIOConfig gpioconfig, uint8_t value);


const _SPIGPIO SPIGPIOsGn = {
	{&GPIOA, 4},
	{&GPIOA, 5},
	{&GPIOA, 6},
	{&GPIOA, 7},
	{&GPIOC, 4},
};

const _SPIGPIO SPIGPIOsRd = {
	{&GPIOB, 12},
	{&GPIOB, 13},
	{&GPIOB, 14},
	{&GPIOB, 15},
	{&GPIOC, 6},
};



void SPIInit(Color color){
	SPIHandle *hSPI;
	_SPIGPIO gpios;
	
	switch(color){
		case Gn:
			hSPI = &hSPIGn;
			hSPI -> instance = &SPI1;
			hSPI -> gpios = SPIGPIOsGn;
			break;
		case Rd:
			hSPI = &hSPIRd;
			hSPI -> instance = &SPI2;
			hSPI -> gpios = SPIGPIOsRd;
			break;
	}
	
	gpios = hSPI->gpios;
	switch(color){
		case Gn:
			PeripheryEnable(RCC_SPI1);
			break;
		case Rd:
			PeripheryEnable(RCC_SPI2);
			break;
	}
	SPIGPIOConfig(gpios.latch,	GPIO_O_STD_PP_02MHZ);
	SPIGPIOConfig(gpios.clock,	GPIO_O_ALT_PP_02MHZ);
	SPIGPIOConfig(gpios.input,	GPIO_I_FLOATING);
	SPIGPIOConfig(gpios.output,	GPIO_O_ALT_PP_02MHZ);
	SPIGPIOConfig(gpios.oe,			GPIO_O_STD_PP_02MHZ);
	
	hSPI->instance->CR1 |= 
							(BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
							| MASK_SPI_CR1_CPOL 												// second clock transition is the first data capture edge
							| MASK_SPI_CR1_SSM
							| MASK_SPI_CR1_SSI
							| MASK_SPI_CR1_MSTR;												// master configuration
	/*
	hSPI->instance->CR2 |= //MASK_SPI_CR2_TXEIE
							 MASK_SPI_CR2_SSOE;*/
	hSPI->instance->CR1 |= MASK_SPI_CR1_SPE;	
	
	
}

void SPIGPIOConfig(_GPIOConfig gpioconfig, uint8_t value){
	ConfigureGPIO(gpioconfig.gpio,gpioconfig.pin,value);
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


void testSPIGnRun(){
	Queue buffer;
	uint32_t data;

	
	
	init(&buffer);
	push(&buffer,0x12345678);
	
		
	
	data=pop(&buffer);
	SPIEmit(&hSPIGn,data);
	
	
}

void testSPIRdRun(){
	Queue buffer;
	uint32_t data;

	
	
	init(&buffer);
	push(&buffer,0x12345678);
	
		
	
	data=pop(&buffer);
	SPIEmit(&hSPIRd,data);
	
	
}


