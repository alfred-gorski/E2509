//
// HW_RTC.h
//

#ifndef __HW_RTC_H__
# define __HW_RTC_H__

# include <RB_RTC.h>

extern RegisterBankRTC volatile RTC;

# define INVALID_RTC_VALUE      (~0U)

WORD ReadRTCValueUnCond(void);
WORD ReadRTCValue      (void);

#endif




















































































