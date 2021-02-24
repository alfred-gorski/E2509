//
// RB_EXTI.h
//

#ifndef __RB_EXTI_H__
# define __RB_EXTI_H__

# include <Compiler.h>

/// EXTI register bank.
/// STM32F103 EXTernal Interrupta (EXTI). See reference manual, chapter 9
typedef struct __reg_bank_EXTI
{
  WORD IMR;                                           ///< Interrupt mask register.
  WORD EMR;                                           ///< Event mask register.
  WORD RTSR;                                          ///< Rising trigger selection register.
  WORD FTSR;                                          ///< Falling trigger selection register.
  WORD SWIER;                                         ///< Software interrupt event register.
  WORD PR;                                            ///< Pending register.
} RegisterBankEXTI;

// EXTI

# define INDX_EXTI_PVD          16

# define INDX_EXTI_IMR_PVD      INDX_EXTI_PVD

# define INDX_EXTI_EMR_PVD      INDX_EXTI_PVD

# define INDX_EXTI_FTSR_PVD     INDX_EXTI_PVD

# define INDX_EXTI_RTSR_PVD     INDX_EXTI_PVD

# define INDX_EXTI_PR_PVD       INDX_EXTI_PVD
# define MASK_EXTI_PR_PVD       (1U << INDX_EXTI_PR_PVD)

#endif








































































