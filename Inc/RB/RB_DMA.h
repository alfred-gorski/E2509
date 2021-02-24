//
// RB_DMA.h
//

#ifndef __RB_DMA_H__
# define __RB_DMA_H__

# include <Compiler.h>

# define DMA_CHAN_NUM           7                     ///< Anzahl der DMA-Kanäle.

/// DMA register bank.
/// STM32F103 Direct Memory Access (DMAx). See reference manual, chapter 10
typedef struct __reg_bank_DMA
{
  WORD ISR;                                           ///< Interrupt status register.
  WORD IFCR;                                          ///< Interrupt flag clear register.

  /// DMA channel register bank.
  /// Jeder DMA-Kanal hat eigene Register. Diese sind in dieser Struktur zusammengefasst.
  struct Channel
  {
    WORD CCR;                                         ///< Channel configuration register.
    WORD CNDTR;                                       ///< Channel number of data cycles register.
    WORD CPAR;                                        ///< Channel peripheral address register.
    WORD CMAR;                                        ///< Channel memory address register.
    WORD reserved;
  };

  struct Channel allChannels[DMA_CHAN_NUM];           ///< Channel configurations.
} RegisterBankDMA;

// CCR

# define INDX_DMA_CCR_MEM2MEM   14
# define MASK_DMA_CCR_MEM2MEM   (1U << INDX_DMA_CCR_MEM2MEM)

# define INDX_DMA_CCR_MINC      7
# define MASK_DMA_CCR_MINC      (1U << INDX_DMA_CCR_MINC)

# define INDX_DMA_CCR_PINC      6
# define MASK_DMA_CCR_PINC      (1U << INDX_DMA_CCR_PINC)

# define INDX_DMA_CCR_CIRC      5
# define MASK_DMA_CCR_CIRC      (1U << INDX_DMA_CCR_CIRC)

# define INDX_DMA_CCR_DIR       4
# define MASK_DMA_CCR_DIR       (1U << INDX_DMA_CCR_DIR)

# define INDX_DMA_CCR_TCIE      1
# define MASK_DMA_CCR_TCIE      (1U << INDX_DMA_CCR_TCIE)

# define INDX_DMA_CCR_EN        0
# define MASK_DMA_CCR_EN        (1U << INDX_DMA_CCR_EN)

# define INDX_DMA_CCR_MSIZE     10
# define MASK_DMA_CCR_MSIZE_BYTE (0U << INDX_DMA_CCR_MSIZE)
# define MASK_DMA_CCR_MSIZE_HWRD (1U << INDX_DMA_CCR_MSIZE)
# define MASK_DMA_CCR_MSIZE_WORD (2U << INDX_DMA_CCR_MSIZE)
# define MASK_DMA_CCR_MSIZE     (3U << INDX_DMA_CCR_MSIZE)

# define INDX_DMA_CCR_PSIZE     8
# define MASK_DMA_CCR_PSIZE_BYTE (0U << INDX_DMA_CCR_PSIZE)
# define MASK_DMA_CCR_PSIZE_HWRD (1U << INDX_DMA_CCR_PSIZE)
# define MASK_DMA_CCR_PSIZE_WORD (2U << INDX_DMA_CCR_PSIZE)
# define MASK_DMA_CCR_PSIZE     (3U << INDX_DMA_CCR_PSIZE)

# define INDX_DMA_CCR_PL        12
# define MASK_DMA_CCR_PL_LOW    (0U << INDX_DMA_CCR_PL)
# define MASK_DMA_CCR_PL_MEDIUM (1U << INDX_DMA_CCR_PL)
# define MASK_DMA_CCR_PL_HIGH   (2U << INDX_DMA_CCR_PL)
# define MASK_DMA_CCR_PL_VHGH   (3U << INDX_DMA_CCR_PL)
# define MASK_DMA_CCR_PL        (3U << INDX_DMA_CCR_PL)

#endif 



























