#include <U_DrvSPI.h>
#include <HW_GPIO.h>
#include <HW_SPI.h>



void SPI1Init(){
	
	
	
	
	/// GPIO Config
	
	// CLK1
	ConfigureGPIO(&GPIOA, 5, GPIO_O_ALT_PP_02MHZ);
	// SDO1
	ConfigureGPIO(&GPIOA, 6, GPIO_O_ALT_PP_02MHZ);
	// SDI1
	ConfigureGPIO(&GPIOA, 7, GPIO_I_FLOATING);
	// LA1
	ConfigureGPIO(&GPIOA, 4, GPIO_O_ALT_PP_02MHZ);
	
	
	// CR1 config
	SPI1.CR1 |= (BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
						| MASK_SPI_CR1_CPHA 										// second clock transition is the first data capture edge
						| (!MASK_SPI_CR1_DFF) 									// data frame format 8bit
						| MASK_SPI_CR1_MSTR;										// master configuration
	
	SPI1.CR2 |= 
						 MASK_SPI_CR2_TXEIE										//buffer empty interrupt enable
						| MASK_SPI_CR2_SSOE;									// SS output enable
	
	SPI1.CR1 |= MASK_SPI_CR1_SPE;										//SPI enable
	
	
	
}

void SPI2Init(){
	
	
	/// GPIO Config
	
	// CLK2
	ConfigureGPIO(&GPIOB, 13, GPIO_O_ALT_PP_02MHZ);
	// SDO2
	ConfigureGPIO(&GPIOB, 14, GPIO_O_ALT_PP_02MHZ);
	// SDI2
	ConfigureGPIO(&GPIOB, 15, GPIO_I_FLOATING);
	// LA2
	ConfigureGPIO(&GPIOB, 12, GPIO_O_ALT_PP_02MHZ);
	
	
	// CR1 config
	SPI2.CR1 |= (BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
						| MASK_SPI_CR1_CPHA 										// second clock transition is the first data capture edge
						| (!MASK_SPI_CR1_DFF) 									// data frame format 8bit
						| MASK_SPI_CR1_MSTR;										// master configuration
	
	// CR2 config
	SPI2.CR2 |= 
						 MASK_SPI_CR2_TXEIE										//buffer empty interrupt enable
						| MASK_SPI_CR2_SSOE;									// SS output enable
	
	SPI2.CR1 |= MASK_SPI_CR1_SPE;										//SPI enable
	
	
}


int SPT_Transmit(SPI_HandelTypDef *hspi,BYTE *Data,BYTE Size){
	
	BYTE TxCount;
	BYTE TimeOutCount=0;
	
	
	
	//info set
	hspi->pTxBuffer=Data;
	TxCount=Size/8;

	// Transmit data in 8 Bit mode 
	hspi->Status=BUSY;
	hspi->Instance->dontTouchMe=*hspi->pTxBuffer;
	hspi->pTxBuffer+=sizeof(BYTE);
	TxCount--;
	
	// Transmit data in 8 Bit mode 
	while(TxCount>0){
		// Wait until TXE flag is set to send data 
		if(hspi->Instance->SR&MASK_SPI_SR_TXE==MASK_SPI_SR_TXE){
			hspi->Instance->dontTouchMe=*hspi->pTxBuffer;
			hspi->pTxBuffer+=sizeof(BYTE);
			TxCount--;
		}
		//TimeOut error
		else{
			TimeOutCount++;
				if(TimeOutCount==TIMEOUT){
					hspi->Status=ERROR;
					
				}
		}
		
	}

	hspi->Status=OK;
	
	if(hspi->Status==ERROR||BUSY)
		return ERROR_SEND;
	else
		return SUCCEED_SEND;


}
