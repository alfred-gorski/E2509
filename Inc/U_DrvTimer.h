#ifndef U_DRVTIMER_H
#define U_DRVTIMER_H

#include <Compiler.h>
#include <HW_NVIC.h>
#include <HW_STK.h>
#include <HW_TIM.h>

/// user configurable	macro, defines global brightness in percentage, the
/// value ranges from 1 to 100.
#define GLOBAL_BRIGHTNESS_PERCENT 90

typedef void (*Callback)(void);

/** @struct TimerHandle
 *	@brief control the Timer action. The Period is calculated out with
 *	(pscValue+1) * (arrValue+1) /72 M. If time out, callback funtion
 *	onTimeUpdateEvent wil be called
 */
typedef struct {
  RegisterBankTIM volatile *instance; ///< reference to RegisterBank
  const uint32_t RCC;                 ///< RCC_TIMX register
  const uint32_t irq;                 ///< NIVC_TIMX register
  const uint32_t pscValue;
  const uint32_t arrValue;
  Callback onTimeUpdateEvent;
} TimerHandle;

void timerInit(const TimerHandle *const hTimer);

#endif
