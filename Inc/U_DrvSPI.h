#ifndef U_DrvSPI_H
#define U_DrvSPI_H

#include <U_DrvSPI.h>
#include <HW_GPIO.h>
#include <HW_SPI.h>
#include <Compiler.h>


#define TIMEOUT 2000

#define		SUCCEED_SEND  0
#define		ERROR_SEND		1


typedef enum
{
  OK       = 0,
  ERROR,    
  BUSY
	
}StatusTypeDef;



	




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
	BYTE 							*pTxBuffer;
	StatusTypeDef			Status;
	
	
	
}SPI_HandelTypDef;







void SPI1Init(void);
void SPI2Init(void);




int SPT_Transmit(SPI_HandelTypDef *hspi,WORD *Data,BYTE Size);









#endif
