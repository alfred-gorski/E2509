#ifndef U_DRVTIMER_H
#define U_DRVTIMER_H


# include <Compiler.h>
#include <HW_STK.h>

typedef struct{
	RegisterBankTIM	volatile *instance;
	
	
}TimerHandle;


void delay_us(WORD nus);


#endif



