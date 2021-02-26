#include <HW_GPIO.h>
#include <Compiler.h>
#include <stdint.h>

typedef struct _GPIO
{
		RegisterBankGPIO volatile * const GPIOx;
		unsigned const pin;
} Def_GPIO;




BYTE GPIO_An_Init(void);

void GPIO_SetPin(RegisterBankGPIO volatile * const GPIOx, unsigned const pin);

void GPIO_ResetPin(RegisterBankGPIO volatile * const GPIOx, unsigned const pin);

