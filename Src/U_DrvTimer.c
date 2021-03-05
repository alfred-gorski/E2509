/**
 * @file 				U_DrvTimer.c
 * @brief  	    Timer call with TIM2,TIM3
 * @details     use callback-function with the help of TIM2&TIM3, Setting the
 * key for the function im Example.c
 * @version 		1.2.0
 */

#include <Compiler.h>

#include <HW_RCC.h>
#include <HW_STK.h>
#include <HW_TIM.h>
#include <RB_NVIC.h>

#include <U_DrvTimer.h>
#include <U_LEDMatrix.h>

extern uint8_t volatile colSwitch;
extern uint8_t volatile imageSwitch;
extern ImageHandle hImage;

void timerEn(TimerHandle *hTimer);
void timerStart(TimerHandle *hTimer);

/// @brief Timer callback functions definition
void Timer2Callback(void) { colSwitch = 1; }
void Timer3Callback(void) { imageSwitch = (~imageSwitch) & 1; }
void Timer4Callback(void) { ImageOutEnOff(&hImage); }

/// Timer configurations
TimerHandle Timer2 = {&TIM2,  RCC_TIM2, NVIC_TIM2,
                      72 - 1, 100 - 1,  &Timer2Callback};
TimerHandle Timer3 = {&TIM3,    RCC_TIM3,  NVIC_TIM3,
                      7200 - 1, 10000 - 1, &Timer3Callback};
TimerHandle Timer4 = {
    &TIM4,          RCC_TIM4, NVIC_TIM4, 72 - 1, GLOBAL_BRIGHTNESS_PERCENT - 1,
    &Timer4Callback};

void timerInit(TimerHandle *const hTimer) {
  /// Enable RCC
  PeripheryEnable(hTimer->RCC);

  hTimer->instance->PSC = hTimer->pscValue;
  hTimer->instance->ARR = hTimer->arrValue;
  hTimer->instance->DIER |= MASK_TIM_DIER_UIE;
  hTimer->instance->SR &= ~MASK_TIM_SR_UIF;

  timerEn(hTimer);
  timerStart(hTimer);
}

void timerEn(TimerHandle *hTimer) { hTimer->instance->CR1 |= MASK_TIM_CR1_CEN; }

/// @brief IRQ Enable
void timerStart(TimerHandle *hTimer) { InterruptEnable(hTimer->irq); }

/// @brief when time out, configure Timer and call the handler.
void timerInterruptHandler(TimerHandle *hTimer) {
  hTimer->instance->CR1 &= ~MASK_TIM_CR1_CEN;
  hTimer->instance->CNT = 0;
  hTimer->instance->SR &= ~MASK_TIM_SR_UIF;
  hTimer->onTimeUpdateEvent();
  hTimer->instance->CR1 |= MASK_TIM_CR1_CEN;
}

void IRQ_TIM2(void) { timerInterruptHandler(&Timer2); }

void IRQ_TIM3(void) { timerInterruptHandler(&Timer3); }

void IRQ_TIM4(void) { timerInterruptHandler(&Timer4); }
