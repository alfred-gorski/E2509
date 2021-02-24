//
// RB_BKP.h
//

#ifndef __RB_BKP_H__
# define __RB_BKP_H__

# include <Compiler.h>

/// Backup register bank.
/// STM32F103 Backup registers (BKP). See reference manual, chapter 5.
typedef struct __reg_bank_BKP
{
  WORD reserved;
  NativeDataType DR[10];                              ///< Backup data registers.
  WORD RTCCR;                                         ///< RTC control register.
  WORD CR;                                            ///< Control register.
  WORD CSR;                                           ///<
} RegisterBankBKP;

// CR

# define INDX_PWR_CR_PVDE       4                     // Power voltage detector enable
# define MASK_PWR_CR_PVDE       (1U << INDX_PWR_CR_PVDE)       

# define INDX_PWR_CR_PLS        5                     // PVD level selection
# define MASK_PWR_CR_PLS_2_9V   (7U << INDX_PWR_CR_PLS)        
# define MASK_PWR_CR_PLS_2_8V   (6U << INDX_PWR_CR_PLS)        
# define MASK_PWR_CR_PLS_2_7V   (5U << INDX_PWR_CR_PLS)        
# define MASK_PWR_CR_PLS_2_6V   (4U << INDX_PWR_CR_PLS)        

#endif
















































































