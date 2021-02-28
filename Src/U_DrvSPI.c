#include <U_DrvSPI.h>
#include <HW_GPIO.h>
#include <HW_SPI.h>
#include <Compiler.h>

const SPIGPIO SPIGn = {
	{&GPIOA, 4},
	{&GPIOA, 5},
	{&GPIOA, 6},
	{&GPIOA, 7},
	{&GPIOC, 4},
};

const SPIGPIO SPIRed = {
	{&GPIOB, 12},
	{&GPIOB, 13},
	{&GPIOB, 14},
	{&GPIOB, 15},
	{&GPIOC, 6},
};




static RegisterBankSPI volatile *pspi1 = &SPI1;
static RegisterBankSPI volatile *pspi2 = &SPI2;

void SPI1Init(void);
void SPI2Init(void);

void SPIInit(void){
	SPI1Init();
	SPI2Init();
}

void SPI1Init(void){
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
							| MASK_SPI_CR1_SSI												// second clock transition is the first data capture edge
							| INDX_SPI_CR1_SSM
							| MASK_SPI_CR1_MSTR;										// master configuration
	
	
	
	// TODO: SPI1 muss be setted as this with unknown reasion
	pspi1->CR2 |= //MASK_SPI_CR2_TXEIE
							 MASK_SPI_CR2_SSOE;
							
	//SPI enable
	pspi1->CR1 |= MASK_SPI_CR1_SPE;			
	
	
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
	
	
	// CR1 config
	pspi2->CR1 |= (BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
							| MASK_SPI_CR1_CPOL 												// second clock transition is the first data capture edge
							| MASK_SPI_CR1_SSM
							| MASK_SPI_CR1_SSI
							| MASK_SPI_CR1_MSTR;												// master configuration
						
	
	//SPI enable
	pspi2->CR1 |= MASK_SPI_CR1_SPE;										
	
	
}




int SPI_Transmit(SPI_HandelTypDef *hspi,WORD *Data){
	
	BYTE TxCount = 0;
	BYTE TimeOutCount = 0;
	WORD tmpData = *Data;
	BYTE pick = 0;
	
	hspi->Status = BUSY;
	while(TxCount < 4 && TimeOutCount < TIMEOUT_THRESHOLD ){
		if((hspi->Instance->SR&MASK_SPI_SR_TXE)==MASK_SPI_SR_TXE){
			pick = tmpData & SIZE_8_MASK;
			tmpData = tmpData >> 8;
			hspi->Instance->DR=pick;
			TxCount++;
		}else{
			TimeOutCount++;
			if(TimeOutCount==TIMEOUT_THRESHOLD){
				hspi->Status=ERROR;	
			}
		}
	}
	if(hspi->Status==BUSY){
		hspi->Status=OK;
		return SUCCEED_SEND;
	}else{
		return ERROR_SEND;
	}
}


