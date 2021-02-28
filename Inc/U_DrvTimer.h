#ifndef U_DRVTIMER_H
#define U_DRVTIMER_H


# include <Compiler.h>
#include <HW_STK.h>
#include <HW_NVIC.h>
#include <HW_TIM.h>

typedef void (* Callback)(void); 


typedef struct{
	RegisterBankTIM	volatile *instance;
	const uint32_t RCC;
	const uint32_t irq;
	const uint32_t pscValue;
	const uint32_t arrValue;
	Callback onTimeUpdateEvent;
}TimerHandle;


void timerInit(TimerHandle * const hTimer);
void timerEn(TimerHandle * hTimer);
void timerStart(TimerHandle * hTimer);


	

#endif



