//
// RB_PWR.h
//

#ifndef __RB_PWR_H__
# define __RB_PWR_H__

# include <Compiler.h>

/// PWR register bank.
/// STM32F103 PoWeR control (PWR). See reference manual, chapter 4
typedef struct __reg_bank_PWR
{
  WORD CR;                                            ///< Power control register.
  WORD CSR;                                           ///< Power control/status register.
} RegisterBankPWR;

# define INDX_PWR_CR_PVDE       4                     ///< Power voltage detector enable.
# define MASK_PWR_CR_PVDE       (1U << INDX_PWR_CR_PVDE)

# define INDX_PWR_CR_PLS        5                     ///< PVD level selection.
# define MASK_PWR_CR_PLS_2_9V   (7U << INDX_PWR_CR_PLS)       
# define MASK_PWR_CR_PLS_2_8V   (6U << INDX_PWR_CR_PLS)        
# define MASK_PWR_CR_PLS_2_7V   (5U << INDX_PWR_CR_PLS)        
# define MASK_PWR_CR_PLS_2_6V   (4U << INDX_PWR_CR_PLS)        

# define INDX_PWR_CR_DBP        8                     ///< Disable backup domain write protection.
# define MASK_PWR_CR_DBP        (1U << INDX_PWR_CR_DBP)

#endif
















































































