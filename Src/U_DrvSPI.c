#include <U_DrvSPI.h>
#include <HW_GPIO.h>
#include <HW_SPI.h>

static RegisterBankSPI volatile *pspi = &SPI1;

void SPI1Init(){
	
	
	
	
	
	/// GPIO Config_Gn
	
	// CLK_Gn
	ConfigureGPIO(&GPIOA, 5, GPIO_O_ALT_PP_02MHZ);
	// SDO_Gn
	ConfigureGPIO(&GPIOA, 6, GPIO_O_ALT_PP_02MHZ);
	// SDI_Gn
	ConfigureGPIO(&GPIOA, 7, GPIO_I_FLOATING);
	// LA_Gn
	ConfigureGPIO(&GPIOA, 4, GPIO_O_ALT_PP_02MHZ);
	// EN_Gn
	ConfigureGPIO(&GPIOC, 4, GPIO_O_ALT_PP_02MHZ);
	
	
	
	// CR1 config
	
	
	
	pspi->CR1 |= (BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
						| MASK_SPI_CR1_CPHA 										// second clock transition is the first data capture edge
						| (!MASK_SPI_CR1_DFF) 									// data frame format 8bit
						| MASK_SPI_CR1_MSTR;										// master configuration
	
	pspi->CR2 |= 
						 MASK_SPI_CR2_TXEIE										//buffer empty interrupt enable
						| MASK_SPI_CR2_SSOE;									// SS output enable
	
	pspi->CR1 |= MASK_SPI_CR1_SPE;										//SPI enable
	
	
	
}

void SPI2Init(){
	
	
	/// GPIO Config
	
	// CLK_Rd
	ConfigureGPIO(&GPIOB, 13, GPIO_O_ALT_PP_02MHZ);
	// SDO_Rd
	ConfigureGPIO(&GPIOB, 14, GPIO_O_ALT_PP_02MHZ);
	// SDI_Rd
	ConfigureGPIO(&GPIOB, 15, GPIO_I_FLOATING);
	// LA_Rd
	ConfigureGPIO(&GPIOB, 12, GPIO_O_ALT_PP_02MHZ);
	// EN_Rd
	ConfigureGPIO(&GPIOC, 6, GPIO_O_ALT_PP_02MHZ);
	
	
	// CR2 config
	SPI2.CR1 |= (BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
						| MASK_SPI_CR1_CPHA 										// second clock transition is the first data capture edge
						| (!MASK_SPI_CR1_DFF) 									// data frame format 8bit
						| MASK_SPI_CR1_MSTR;										// master configuration
	
	// CR2 config
	SPI2.CR2 |= 
						 //MASK_SPI_CR2_TXEIE										//buffer empty interrupt enable
						 MASK_SPI_CR2_SSOE;									// SS output enable
	
	SPI2.CR1 |= MASK_SPI_CR1_SPE;										//SPI enable
	
	
}




int SPT_Transmit(SPI_HandelTypDef *hspi,WORD *Data,BYTE Size){
	
	BYTE TxCount;
	BYTE TimeOutCount=0;
	hspi->pTxBuffer  = (uint8_t *)Data;


	
	//info set
	
	TxCount=Size/8;

	// Transmit data in 8 Bit mode 
	hspi->Status=BUSY;
	hspi->Instance->DR=*hspi->pTxBuffer;
	hspi->pTxBuffer+=sizeof(BYTE);
	TxCount--;
	
	// Transmit data in 8 Bit mode 
	while(TxCount>0){
		// Wait until TXE flag is set to send data 
		if((hspi->Instance->SR&MASK_SPI_SR_TXE)==MASK_SPI_SR_TXE){
			
			hspi->Instance->DR=*hspi->pTxBuffer;
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
