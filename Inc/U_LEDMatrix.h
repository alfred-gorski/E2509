#include <HW_GPIO.h>
#include <Compiler.h>
#include <stdint.h>

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
//Latch  for Gn
#define La_Gn_Set GPIO_SetPin(&GPIOA, 4)

//Enable for Rd
#define En_Rd_Set GPIO_SetPin(&GPIOC, 6)
//Latch  for Rd
#define La_Rd_Set GPIO_SetPin(&GPIOB, 12)


