#include <Compiler.h>


#include <U_LEDMatrix.h>
#include <U_GPIOConfig.h>
#include <U_DrvSPI.h>



static const AnTType AnT = {
//static const _GPIOConfig AnT[] = {
															{&GPIOA, 12}, //antr1
															{&GPIOA, 11}, //antr2
															{&GPIOA, 10}, //antr3
															{&GPIOA, 9 }, //antr4
															{&GPIOA, 8 }, //antr5
															{&GPIOC, 9 }, //antr6
															{&GPIOC, 8 }, //antr7
															{&GPIOC, 7 }, //antr8
};



void AnTInit(void){
	int i=0;
	for(i=0;i<ANT_LEN;i++){
		GPIOConfig(AnT[i],GPIO_O_STD_PP_02MHZ);
		setGPIOPin(AnT[i]);
	}
}


void AnTOnAt(uint8_t index){
	resetGPIOPin(AnT[index]);
}

void AnTOffAt(uint8_t index){
	setGPIOPin(AnT[index]);
}



