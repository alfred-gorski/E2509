#ifndef U_DrvSPI_H
#define U_DrvSPI_H

#include <U_DrvSPI.h>
#include <HW_GPIO.h>
#include <HW_SPI.h>
#include <Compiler.h>


#define TIMEOUT_THRESHOLD 2000
#define SIZE_8_MASK ( 1 << 8) - 1




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

typedef struct 
{
	RegisterBankSPI	 volatile	*Instance;
	BYTE							*pTxBuffer;
	BYTE 							*pRxBuffer;
	SPISendStatus			Status;
}SPI_HandelTypDef;



void SPI1Init(void);
void SPI2Init(void);




int SPI_Transmit(SPI_HandelTypDef *hspi,WORD *Data);






#endif
