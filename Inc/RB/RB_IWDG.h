//
// RB_IWDG.h
//

#ifndef __RB_IWDG_H__
# define __RB_IWDG_H__

# include <Compiler.h>

/// Independant Watch Dog register bank.
/// STM32F103 Independant Watchdog (IWDG). See reference manual, chapter 17.
typedef struct
{
  WORD KR;                                            ///< Key register.
  WORD PR;                                            ///< Prescaler register.
  WORD RLR;                                           ///< Reload register register.
  WORD SR;                                            ///< Status register.
} RegisterBankIWDG;

#endif


















































































