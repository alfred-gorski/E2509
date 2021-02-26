#include <U_LEDMatrix.h>
#include <Compiler.h>
#include <stdio.h>


BYTE GPIO_An_Init(){
	static const Def_GPIO An[] = 	{
																&GPIOA, 12, //antr1
																&GPIOA, 11, //antr2
																&GPIOA, 10, //antr3
																&GPIOA, 9 , //antr4
																&GPIOA, 8 , //antr5
																&GPIOC, 9 , //antr6
																&GPIOC, 8 , //antr7
																&GPIOC, 7 , //antr8
		
																};

	uint32_t i;
	for(i=0;i<8;i++){
		ConfigureGPIO(An[i].GPIOx, An[i].pin, GPIO_O_ALT_PP_02MHZ);
	
	}
	
	return SUCCEED_SEND;
}

void GPIO_SetPin(RegisterBankGPIO volatile * const GPIOx, unsigned const pin){
	GPIOx->BSRR |= (1<<pin);
	
}


void GPIO_ResetPin(RegisterBankGPIO volatile * const GPIOx, unsigned const pin){
	GPIOx->BRR |= (1<<pin);
	
}

