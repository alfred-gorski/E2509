//
// RB_AFIO.H
//

/// \file RB_USART.h
/// Registerbank-Datentyp für AFIO.

#ifndef __RB_AFIO_H__
# define __RB_AFIO_H__

# include <Compiler.h>

/// AFIO register bank.
/// STM32F103 Alternate Function I/O (AFIO). See reference manual, chapter 8
typedef struct RegisterBankAFIO
{
  WORD EVCR;                                          ///< Event control register.
  WORD MAPR;                                          ///< AF remap and debug I/O configuration register.
  WORD EXTICR[4];                                     ///< External interrupt configuration registers.
} RegisterBankAFIO;

// MAPR

# define INDX_AFIO_MAPR_SPI1    0
# define MASK_AFIO_MAPR_SPI1    (1U << INDX_AFIO_MAPR_SPI1_REMAP)

# define INDX_AFIO_MAPR_USART1  2
# define MASK_AFIO_MAPR_USART1  (1U << INDX_AFIO_MAPR_USART1)

# define INDX_AFIO_MAPR_USART2  3
# define MASK_AFIO_MAPR_USART2  (1U << INDX_AFIO_MAPR_USART2)

# define INDX_AFIO_MAPR_USART3  4
# define MASK_AFIO_MAPR_USART3  (3U << INDX_AFIO_MAPR_USART3)
# define MASK_AFIO_MAPR_USART3_FULL (3U << INDX_AFIO_MAPR_USART3)
# define MASK_AFIO_MAPR_USART3_PART (1U << INDX_AFIO_MAPR_USART3)
# define MASK_AFIO_MAPR_USART3_NONE (0U << INDX_AFIO_MAPR_USART3)

# define INDX_AFIO_MAPR_TIM1    6
# define MASK_AFIO_MAPR_TIM1    (3U << INDX_AFIO_MAPR_TIM1)
# define MASK_AFIO_MAPR_TIM1_FULL  (3U << INDX_AFIO_MAPR_TIM1)
# define MASK_AFIO_MAPR_TIM1_PART  (1U << INDX_AFIO_MAPR_TIM1)
# define MASK_AFIO_MAPR_TIM1_NONE  (0U << INDX_AFIO_MAPR_TIM1)

# define INDX_AFIO_MAPR_TIM2    8
# define MASK_AFIO_MAPR_TIM2    (3U << INDX_AFIO_MAPR_TIM2)
# define MASK_AFIO_MAPR_TIM2_FULL  (3U << INDX_AFIO_MAPR_TIM2)
# define MASK_AFIO_MAPR_TIM2_PARTb (2U << INDX_AFIO_MAPR_TIM2)
# define MASK_AFIO_MAPR_TIM2_PARTa (1U << INDX_AFIO_MAPR_TIM2)
# define MASK_AFIO_MAPR_TIM2_NONE  (0U << INDX_AFIO_MAPR_TIM2)

# define INDX_AFIO_MAPR_TIM3    10
# define MASK_AFIO_MAPR_TIM3    (3U << INDX_AFIO_MAPR_TIM3)
# define MASK_AFIO_MAPR_TIM3_FULL  (3U << INDX_AFIO_MAPR_TIM3)
# define MASK_AFIO_MAPR_TIM3_PART  (2U << INDX_AFIO_MAPR_TIM3)
# define MASK_AFIO_MAPR_TIM3_NONE  (0U << INDX_AFIO_MAPR_TIM3)

# define INDX_AFIO_MAPR_TIM4    12
# define MASK_AFIO_MAPR_TIM4    (1U << INDX_AFIO_MAPR_TIM4)
# define MASK_AFIO_MAPR_TIM4_FULL  (1U << INDX_AFIO_MAPR_TIM4)
# define MASK_AFIO_MAPR_TIM4_NONE  (0U << INDX_AFIO_MAPR_TIM4)

#endif








































