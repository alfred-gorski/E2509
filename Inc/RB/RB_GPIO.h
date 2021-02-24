//
// RB_GPIO.h
//

/// \file RB_GPIO.h
/// Registerbank-Datentyp für GPIO.

#ifndef __RB_GPIO_H__
# define __RB_GPIO_H__

# include <Compiler.h>

/// GPIO register bank.
/// STM32F103 General Purpose I/O (GPIO). See reference manual, chapter 8
typedef struct __reg_bank_GPIO
{
  WORD CRL;                                           ///< Configuration register low.
  WORD CRH;                                           ///< Configuration register high.
  WORD IDR;                                           ///< Input data register.
  WORD ODR;                                           ///< Output data register.
  WORD BSRR;                                          ///< Bit set/reset register.
  WORD BRR;                                           ///< Bit reset register.
  WORD LCKR;                                          ///< Lock register.
} RegisterBankGPIO;

#endif












































































