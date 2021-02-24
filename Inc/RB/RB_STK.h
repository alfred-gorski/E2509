//
// RB_STK.H
//

/// \file RB_STK.h
/// Registerbank-Datentyp für STK (system tick).

#ifndef __RB_STK_H__
# define __RB_STK_H__

# include <Compiler.h>

/// STK register bank.
/// STM32Fxxx System Tick, see section 4.4 of STM32F10xxx Cortex-M3 programming manual (PM0056)
typedef struct __reg_bank_STK
{
  WORD dontTouchMe[4];
  WORD CTRL;                    ///< Control and status register.
  WORD LOAD;                    ///< Reload value register.
  WORD VAL;                     ///< Current value register.
  WORD CALIB;                   ///< Calibration value register.
} RegisterBankSTK;

// CTRL

# define MASK_STK_CTRL_ENABLE   1U
# define MASK_STK_CTRL_TICKINT  2U
# define MASK_STK_CTRL_CLKSOURCE 4U
                                                              
#endif











































































