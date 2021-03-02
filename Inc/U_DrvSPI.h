#ifndef U_DrvSPI_H
#define U_DrvSPI_H

#include <HW_GPIO.h>
#include <HW_SPI.h>
#include <Compiler.h>
#include <U_GPIOConfig.h>


#define TIMEOUT_THRESHOLD 2000
#define SIZE_8_MASK ( 1 << 8) - 1



typedef enum{
	Gn=0,
	Rd
}Color;

typedef enum{
  OK       = 0,
  ERROR,    
  BUSY
}SPISendStatus;

typedef enum{
	BaudRateScaler_2=0,
	BaudRateScaler_4,
	BaudRateScaler_8,
	BaudRateScaler_16,
	BaudRateScaler_32,
	BaudRateScaler_64,
	BaudRateScaler_128,
	BaudRateScaler_256
}BaudRate;



typedef struct{
	_GPIOConfig latch;
	_GPIOConfig clock;
	_GPIOConfig input;
	_GPIOConfig output;
	_GPIOConfig outEn;
}_SPIGPIOs;

typedef struct{
	RegisterBankSPI volatile *instance;
	_SPIGPIOs gpios;
	SPISendStatus status;
}SPIHandle;



void SPIInit(SPIHandle* hSPI, Color color);
int SPIEmit(SPIHandle *hSPI,uint32_t data);
void SPILatch(SPIHandle *hSPI);
void SPIOutEn(SPIHandle *hSPI);
void SPIOutEnOff(SPIHandle *hSPI);


#endif
