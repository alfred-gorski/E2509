//
// RB_FLASH.h
//

/// \file RB_FLASH.h
/// Registerbank-Datentyp für FLASH.

#ifndef __RB_FLASH_H__
# define __RB_FLASH_H__

# include <Compiler.h>

/// Flash memory register bank.
typedef struct __reg_bank_FLASH
{
  WORD ACR;                                           ///< Flash access control register.
  WORD KEYR;                                          ///< FPEC key register.
  WORD OPTKEYR;                                       ///< Flash OPTKEY register.
  WORD SR;                                            ///< Flash status register.
  WORD CR;                                            ///< Flash control register.
  WORD AR;                                            ///< Flash address register.
  WORD OBR;                                           ///< Option byte register.
  WORD WRPR;                                          ///< Write protection register.
} RegisterBankFLASH;

// ACR

# define INDX_FLASH_ACR_PRFTBE  4                     // Prefetch buffer enable
# define MASK_FLASH_ACR_PRFTBE  (1U << INDX_FLASH_ACR_PRFTBE)

// SR

# define INDX_FLASH_SR_BSY      0
# define MASK_FLASH_SR_BSY      (1U << INDX_FLASH_SR_BSY)

# define INDX_FLASH_SR_PGERR    2
# define MASK_FLASH_SR_PGERR    (1U << INDX_FLASH_SR_PGERR)

# define INDX_FLASH_SR_EOP      5
# define MASK_FLASH_SR_EOP      (1U << INDX_FLASH_SR_EOP)

// CR

# define INDX_FLASH_CR_PG       0
# define MASK_FLASH_CR_PG       (1U << INDX_FLASH_CR_PG)

# define INDX_FLASH_CR_PER      1
# define MASK_FLASH_CR_PER      (1U << INDX_FLASH_CR_PER)

# define INDX_FLASH_CR_MER      2
# define MASK_FLASH_CR_MER      (1U << INDX_FLASH_CR_MER)

# define INDX_FLASH_CR_OPTPG    5
# define MASK_FLASH_CR_OPTPG    (1U << INDX_FLASH_CR_OPTPG)

# define INDX_FLASH_CR_OPTER    5
# define MASK_FLASH_CR_OPTER    (1U << INDX_FLASH_CR_OPTER)

# define INDX_FLASH_CR_STRT     6
# define MASK_FLASH_CR_STRT     (1U << INDX_FLASH_CR_STRT)

# define INDX_FLASH_CR_LOCK     7
# define MASK_FLASH_CR_LOCK     (1U << INDX_FLASH_CR_LOCK)

# define INDX_FLASH_CR_OPTWRE   9 
# define MASK_FLASH_CR_OPTWRE   (1U << INDX_FLASH_CR_OPTWRE)

# define INDX_FLASH_CR_EOPIE    12
# define MASK_FLASH_CR_EOPIE    (1U << INDX_FLASH_CR_EOPIE)

// KEYR

# define MASK_FLASH_KEYR_KEY1   0x45670123U
# define MASK_FLASH_KEYR_KEY2   0xCDEF89ABU

// OBR

# define INDX_FLASH_OBR_OPTERR  0
# define MASK_FLASH_OBR_OPTERR  (1U << INDX_FLASH_OBR_OPTERR)

# define INDX_FLASH_OBR_RDPRT   1
# define MASK_FLASH_OBR_RDPRT   (1U << INDX_FLASH_OBR_RDPRT)

#endif



















