#include <Compiler.h>

#include <HW_STK.h>
#include <HW_RCC.h>
#include <HW_TIM.h>
#include <RB_NVIC.h>

#include <U_DrvTimer.h>

extern WORD volatile code;

void Timer2Callback(void){
	
}


void Timer3Callback(void){
	code = 1;
}

TimerHandle Timer2 = {
	&TIM2,
	RCC_TIM2,
	NVIC_TIM2,
	36-1,
	100-1,
	&Timer2Callback
};

TimerHandle Timer3 = {
	&TIM3,
	RCC_TIM3,
	NVIC_TIM3,
	7200-1,
	10000-1,
	&Timer3Callback
};





void timerInit(TimerHandle * const hTimer){
	PeripheryEnable(hTimer->RCC);
	
	hTimer->instance->PSC = hTimer->pscValue;
	hTimer->instance->ARR = hTimer->arrValue;
	hTimer->instance->DIER |= MASK_TIM_DIER_UIE;
	hTimer->instance->SR &= ~MASK_TIM_SR_UIF;
}

void timerEn(TimerHandle * hTimer){
	hTimer->instance->CR1 |=MASK_TIM_CR1_CEN;
}

void timerStart(TimerHandle * hTimer){
	InterruptEnable(hTimer->irq);
}

void timerInterruptHandler(TimerHandle * hTimer){
	hTimer->instance->CR1 &= ~MASK_TIM_CR1_CEN;
	hTimer->instance->CNT = 0;
	hTimer->instance->SR &= ~MASK_TIM_SR_UIF;
	hTimer->onTimeUpdateEvent();
	hTimer->instance->CR1 |= MASK_TIM_CR1_CEN;
}

void IRQ_TIM2(void){
	timerInterruptHandler(&Timer2);
		
}

void IRQ_TIM3(void){
	timerInterruptHandler(&Timer3);
}









