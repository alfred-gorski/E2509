#include <Compiler.h>


#include <U_LEDMatrix.h>
#include <U_GPIOConfig.h>
#include <U_DrvSPI.h>

int volatile code;
int count = 0;
int previous;

void AnTOnAt(uint8_t index);
void AnTOffAt(uint8_t index);

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











void screenOn(SPIHandle* hSPIGn,SPIHandle* hSPIRd){
	while(code == 1){
		code =0;
		SPIOutEnOff(hSPIGn);
		SPIOutEnOff(hSPIRd);
		AnTOnAt(count);
		previous = count-1;
		if(count == 0){
			previous = 7;
		}
		AnTOffAt(previous);
		count++;
		if (count == 8){
			count = 0;
		}
		SPIEmit(hSPIGn,0x12345678);
		SPIEmit(hSPIRd,0xABCDEF12);
		SPILatch(hSPIGn);
		SPILatch(hSPIRd);
		SPIOutEn(hSPIGn);
		SPIOutEn(hSPIRd);

	
	}
	
}

























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



