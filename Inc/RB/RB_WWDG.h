//
// RB_WWDG.H
//

#ifndef __RB_WWDG_H__
# define __RB_WWDG_H__

# include <Compiler.h>

/// Windows Watch Dog register bank.
/// STM32F103 Window Watchdog (WWDG). See reference manual, chapter 18
typedef struct __reg_bank_WWDG
{
  WORD CR;                                            ///< Control register.
  WORD CFR;                                           ///< Configuration register.
  WORD SR;                                            ///< Status register.
} RegisterBankWWDG;

// CR

# define INDX_WWDG_CR_WDGA      7                     ///< Watchdog activation.
# define MASK_WWDG_CR_WDGA      (1U << INDX_WWDG_CR_WDGA)

#endif























































































