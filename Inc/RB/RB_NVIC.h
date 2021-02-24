//
// RB_NVIC.h
//

/// \file RB_NVIC.h
/// Registerbank-Datentyp für NVIC.

#ifndef __RB_NVIC_H__
# define __RB_NVIC_H__

# include <Compiler.h>

/// NVIC register bank.
/// STM32F103 Nested Vector Interrupt Controller (NVIC)
typedef struct __reg_bank_NVIC
{
  WORD ISER[2];
  WORD reserved0[30];
  WORD ICER[2];
  WORD reserved1[30];
  WORD ISPR[2];                                       ///< Interrupt set-pending registers.
  WORD reserved2[30];
  WORD ICPR[2];                                       ///< Interrupt clear-pending registers.
  WORD reserved3[30];
  WORD IABR[2];                                       ///< Interrupt active bit register.
  WORD reserved4[62];

  /// Byte/word-access to IPR.
  union IPRDataType {
    WORD asWord[17];
    BYTE asByte[17 * sizeof(WORD)];
  } IPR;                                              ///< Interrupt pending registers.
} RegisterBankNVIC;

/// SCB register bank.
/// STM32F103 System Control Block (SCB)
typedef struct __reg_bank_SCB
{
  WORD CPUID;
  WORD ICSR;
  WORD VTOR;
  WORD AIRCR;                                         ///< NVIC Application Interrupt and Reset Control Register
  WORD SCR;
  WORD CCR;
  WORD SHPR[3];                                       ///< System Handler Priority Registers
  WORD SHCSR;                                         ///< System Handler Control and State Register
  WORD CFSR;                                          ///< Configurable Fault Status Register(s)
  WORD HFSR;                                          ///< Hard Fault Status Register
  WORD DFSR;                                          ///< Debug Fault Status Register
  WORD MMFAR;
  WORD BFAR;
  WORD AFSR;
} RegisterBankSCB;

// ICSR

# define INDX_SCB_ICSR_PENDSVCCLR 27
# define MASK_SCB_ICSR_PENDSVCCLR (1U << INDX_SCB_ICSR_PENDSVCCLR) 

# define INDX_SCB_ICSR_PENDSVCSET 28
# define MASK_SCB_ICSR_PENDSVCSET (1U << INDX_SCB_ICSR_PENDSVCSET) 

// CCR

# define INDX_SCB_CCR_STKALIGN  9
# define MASK_SCB_CCR_STKALIGN  (1U << INDX_SCB_CCR_STKALIGN)

# define INDX_SCB_CCR_DIV_0_TRP 4
# define MASK_SCB_CCR_DIV_0_TRP (1U << INDX_SCB_CCR_DIV_0_TRP)

# define INDX_SCB_CCR_UNALIGN_TRP 3
# define MASK_SCB_CCR_UNALIGN_TRP (1U << INDX_SCB_CCR_UNALIGN_TRP)

# define INDX_SCB_CCR_NONBASETHRDENA 0
# define MASK_SCB_CCR_NONBASETHRDENA (1U << INDX_SCB_CCR_NONBASETHRDENA)

// SHCSR

# define INDX_SCB_SHCSR_USGFAULTENA 18
# define MASK_SCB_SHCSR_USGFAULTENA (1U << INDX_SCB_SHCSR_USGFAULTENA)

# define INDX_SCB_SHCSR_BUSFAULTENA 17
# define MASK_SCB_SHCSR_BUSFAULTENA (1U << INDX_SCB_SHCSR_BUSFAULTENA)

# define INDX_SCB_SHCSR_MEMFAULTENA 16
# define MASK_SCB_SHCSR_MEMFAULTENA (1U << INDX_SCB_SHCSR_MEMFAULTENA)

#endif













