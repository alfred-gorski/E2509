#include <U_DrvSPI.h>
#include <HW_GPIO.h>
#include <HW_SPI.h>


void SPI1Init(){
	
	
	/// GPIO Config
	
	// CLK
	ConfigureGPIO(&GPIOA, 5, GPIO_O_ALT_PP_02MHZ);
	// SDO
	ConfigureGPIO(&GPIOA, 6, GPIO_O_ALT_PP_02MHZ);
	// SDI
	ConfigureGPIO(&GPIOA, 7, GPIO_I_FLOATING);
	// LA
	ConfigureGPIO(&GPIOA, 4, GPIO_O_ALT_PP_02MHZ);
	
	
	// CR1 config
	SPI1.CR1 |= (BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
						| MASK_SPI_CR1_CPHA 										// second clock transition is the first data capture edge
						| (!MASK_SPI_CR1_DFF) 									// data frame format 8bit
						| MASK_SPI_CR1_MSTR;										// master configuration
	
	//SPI1.CR2 |= 
						// MASK_SPI_CR2_RXNEIE										//
						//| MASK_SPI_CR2_SSOE;
	
	//SPI1.CR1 |= 
	
	
}

