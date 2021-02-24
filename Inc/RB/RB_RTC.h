//
// RB_RTC.h
//

#ifndef __RB_RTC_H__
# define __RB_RTC_H__

# include <Compiler.h>

/// RTC register parts.
/// Einige RTC-Register sind, obwohl 32 Bit breit, in 2 Registern zu je 16 Bits implementiert. 
/// Die Struktur realisiert den Zugriff auf den höherwertigen und niederwertigen Teil.
typedef struct
{
  HWRD high;                                          ///< high half (most significant half word = 16 bits).
  HWRD reserved0;
  HWRD low;                                           ///< low half (least significant half word = 16 bits).
  HWRD reserved1;
} RTCHighLow;

/// RTC register bank.
/// STM32F103 Real-time clock (RTC). See reference manual, chapter 16
typedef struct __reg_bank_RTC
{
  WORD CRH;                                           ///< RTC Control register high part.
  WORD CRL;                                           ///< RTC control register low part.
  RTCHighLow PRL;                                     ///< RTC prescaler load register.
  RTCHighLow DIV;                                     ///< RTC prescaler divider register.
  RTCHighLow CNT;                                     ///< RTC counter register.
  RTCHighLow ALR;                                     ///< RTC alarm register.
} RegisterBankRTC;

// CRL

# define INDX_RTC_CRL_RTOFF     5
# define MASK_RTC_CRL_RTOFF     (1U << INDX_RTC_CRL_RTOFF)

# define INDX_RTC_CRL_CNF       4
# define MASK_RTC_CRL_CNF       (1U << INDX_RTC_CRL_CNF)

# define INDX_RTC_CRL_RSF       3
# define MASK_RTC_CRL_RSF       (1U << INDX_RTC_CRL_RSF)

# define INDX_RTC_CRL_ALRF      1
# define MASK_RTC_CRL_ALRF      (1U << INDX_RTC_CRL_ALRF)

# define INDX_RTC_CRL_SECF      0
# define MASK_RTC_CRL_SECF      (1U << INDX_RTC_CRL_SECF)

// CRH

# define INDX_RTC_CRH_ALRIE     1
# define MASK_RTC_CRH_ALRIE     (1U << INDX_RTC_CRH_ALRIE)

# define INDX_RTC_CRH_SECIE     0
# define MASK_RTC_CRH_SECIE     (1U << INDX_RTC_CRH_SECIE)

#endif













































