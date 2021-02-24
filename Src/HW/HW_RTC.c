//
// HW_RTC.c
//

#include <HW_RTC.h>

RegisterBankRTC volatile RTC __attribute__((at(0x40002800)));

WORD ReadRTCValueUnCond(NO_ARGS)
{
  return (WORD)RTC.CNT.low | ((WORD)RTC.CNT.high << 16);
}

WORD ReadRTCValue(NO_ARGS)
{
  return ((RTC.CRL & MASK_RTC_CRL_RSF) != 0U) ? ReadRTCValueUnCond() : INVALID_RTC_VALUE;
}






















































































