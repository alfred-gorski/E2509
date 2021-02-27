#include <U_DrvSPI.h>
#include <HW_GPIO.h>
#include <HW_SPI.h>

static RegisterBankSPI volatile *pspi1 = &SPI1;

static RegisterBankSPI volatile *pspi2 = &SPI2;

void SPI1Init(){
	
	
	
	
	
	/// GPIO Config_Gn
	
	// CLK_Gn
	ConfigureGPIO(&GPIOA, 5, GPIO_O_ALT_PP_02MHZ);
	// SDO_Gn
	ConfigureGPIO(&GPIOA, 7, GPIO_O_ALT_PP_02MHZ);
	// SDI_Gn
	ConfigureGPIO(&GPIOA, 6, GPIO_I_FLOATING);
	// LA_Gn
	ConfigureGPIO(&GPIOA, 4, GPIO_O_STD_PP_02MHZ);
	// EN_Gn
	ConfigureGPIO(&GPIOC, 4, GPIO_O_STD_PP_02MHZ);
	
	
	
	// CR1 config
	
	
	
	pspi1->CR1 |= (BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
						| MASK_SPI_CR1_CPOL 	
						|MASK_SPI_CR1_SSI												// second clock transition is the first data capture edge
						|INDX_SPI_CR1_SSM
						| MASK_SPI_CR1_MSTR;										// master configuration
	
	pspi1->CR2 |= 
						 MASK_SPI_CR2_TXEIE										//buffer empty interrupt enable
						| MASK_SPI_CR2_SSOE;									// SS output enable
	
	pspi1->CR1 |= MASK_SPI_CR1_SPE;										//SPI enable
	
	
	
}

void SPI2Init(){
	
	
	/// GPIO Config
	
	// CLK_Rd
	ConfigureGPIO(&GPIOB, 13, GPIO_O_ALT_PP_02MHZ);
	// SDO_Rd
	ConfigureGPIO(&GPIOB, 15, GPIO_O_ALT_PP_02MHZ);
	// SDI_Rd
	ConfigureGPIO(&GPIOB, 14, GPIO_I_FLOATING);
	// LA_Rd
	ConfigureGPIO(&GPIOB, 12, GPIO_O_STD_PP_02MHZ);
	// EN_Rd
	ConfigureGPIO(&GPIOC, 6, GPIO_O_STD_PP_02MHZ);
	
	
	// CR2 config
	/*
	pspi2->CR1 |= (BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
						| MASK_SPI_CR1_CPOL 										// second clock transition is the first data capture edge
						| (!MASK_SPI_CR1_DFF) 									// data frame format 8bit
						| MASK_SPI_CR1_MSTR;										// master configuration
			*/
		pspi2->CR1 |= (BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
						| MASK_SPI_CR1_CPOL 										// second clock transition is the first data capture edge
						| MASK_SPI_CR1_SSM
						| MASK_SPI_CR1_SSI
						| MASK_SPI_CR1_MSTR;										// master configuration
						
	
	// CR2 config
	/*SPI2.CR2 |= 
						 //MASK_SPI_CR2_TXEIE										//buffer empty interrupt enable
						 MASK_SPI_CR2_SSOE;									// SS output enable
	*/
	pspi2->CR1 |= MASK_SPI_CR1_SPE;										//SPI enable
	
	
}




int SPI_Transmit(SPI_HandelTypDef *hspi,WORD *Data,BYTE Size){
	
	BYTE TxCount;
	
	BYTE TimeOutCount=0;
	
	hspi->pTxBuffer  = (uint8_t *)Data;


	
	//info set
	
	TxCount=Size/8;

	// Transmit data in 8 Bit mode 
	hspi->Status=BUSY;
	hspi->Instance->DR=*(hspi->pTxBuffer);
	
	hspi->pTxBuffer+=sizeof(BYTE);
	TxCount--;
	
	// Transmit data in 8 Bit mode 
	
	while(TxCount>0){
		// Wait until TXE flag is set to send data 
		if((hspi->Instance->SR&MASK_SPI_SR_TXE)==MASK_SPI_SR_TXE){
			
			
			hspi->Instance->DR=*(hspi->pTxBuffer);
		
			
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
	
	if(hspi->Status==ERROR||hspi->Status==BUSY)
		return ERROR_SEND;
	else
		return SUCCEED_SEND;


}

int TxBuffer_Empty(SPI_HandelTypDef *hspi){
	if((hspi->Instance->SR&MASK_SPI_SR_TXE)==MASK_SPI_SR_TXE)
			return 0;
	else
			return 1;


}		

uint32_t count;
unsigned char x;
unsigned char y;
void SPI_transmit_with_ff(SPI_HandelTypDef *hspi){

	//SPI_Transmit(hspi,&data,32);
	
	
	//*((uint8_t *)&hspi->Instance->DR)=0x12;
	x = 0x10;
	y = 0xCA;
	hspi->Instance->DR = 0x12;
	
	count=8;
	
	while(count>0){
		if((hspi->Instance->SR&MASK_SPI_SR_TXE)==MASK_SPI_SR_TXE){
			hspi->Instance->DR=x;
			count--;	
		}
		
	}

	
}

