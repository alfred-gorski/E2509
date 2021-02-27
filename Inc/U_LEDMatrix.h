#include <HW_GPIO.h>
#include <Compiler.h>
#include <stdint.h>

#include <U_DrvSPI.h>

typedef struct _GPIO
{
		RegisterBankGPIO volatile * const GPIOx;
		unsigned const pin;
} Def_GPIO;




//Function for GPIO
BYTE GPIO_An_Init(void);

void GPIO_SetPin(RegisterBankGPIO volatile * const GPIOx, unsigned const pin);

void GPIO_ResetPin(RegisterBankGPIO volatile * const GPIOx, unsigned const pin);


//Enable for Gn
#define En_Gn_Set GPIO_SetPin(&GPIOC, 4)
//Set  Gn_LAT
#define La_Gn_Set GPIO_SetPin(&GPIOA, 4)

//Enable for Rd
#define En_Rd_Set GPIO_SetPin(&GPIOC, 6)
//Set  Rd_LAT
#define La_Rd_Set GPIO_SetPin(&GPIOB, 12)



//Disable for Gn
#define En_Gn_Reset GPIO_ResetPin(&GPIOC, 4)
//Reset  Gn_LAT
#define La_Gn_Reset GPIO_ResetPin(&GPIOA, 4)

//DIsable for Rd
#define En_Rd_Reset GPIO_ResetPin(&GPIOC, 6)
//Reset  Rd_LAT
#define La_Rd_Reset GPIO_ResetPin(&GPIOB, 12)

void latch_SPI_Gn(void);
void latch_SPI_Rd(void);

void SPI_transmit_with_ff(SPI_HandelTypDef *hspi);
