//
// RB_ADC.h
//

#ifndef __RB_ADC_H__
# define __RB_ADC_H__

# include <Compiler.h>

/// ADC register bank.
/// STM32F103 Analog-to-digital Converter (ADC). See reference manual, chapter 11
typedef struct __reg_bank_ADC
{
  WORD SR;                                            ///< Status register.
  WORD CR1;                                           ///< Control register 1.
  WORD CR2;                                           ///< Control register 2.
  WORD SMPR1;                                         ///< Sample time register 1.
  WORD SMPR2;                                         ///< Sample time register 2.
  WORD JOFR1;                                         ///< Injected channel data offset register 1.
  WORD JOFR2;                                         ///< Injected channel data offset register 2.
  WORD JOFR3;                                         ///< Injected channel data offset register 3.
  WORD JOFR4;                                         ///< Injected channel data offset register 4.
  WORD HTR;                                           ///< Watchdog high threshold register.
  WORD LTR;                                           ///< watchdog low threshold register.
  WORD SQR1;                                          ///< Regular sequence register 1.
  WORD SQR2;                                          ///< Regular sequence register 2.
  WORD SQR3;                                          ///< Regular sequence register 3.
  WORD JSQR;                                          ///< Injected sequence register.
  WORD JDR1;                                          ///< Injected data register 1.
  WORD JDR2;                                          ///< Injected data register 2.
  WORD JDR3;                                          ///< Injected data register 3.
  WORD JDR4;                                          ///< Injected data register 4.
  WORD DR;                                            ///< Regular data register.
} RegisterBankADC;

// SR

# define INDX_ADC_SR_AWD        0                     // Analog watchdog flag
# define MASK_ADC_SR_AWD        (1U << INDX_ADC_SR_AWD)

# define INDX_ADC_SR_EOC        1                     // End of conversion
# define MASK_ADC_SR_EOC        (1U << INDX_ADC_SR_EOC)

// CR1

# define INDX_ADC_CR1_AWDEN     23                    // Analog watchdog enable on regular channels
# define MASK_ADC_CR1_AWDEN     (1U << INDX_ADC_CR1_AWDEN)

# define INDX_ADC_CR1_AWDSGL    9                     // Enable the watchdog on a single channel (0) or all channels (1) in scan mode
# define MASK_ADC_CR1_AWDSGL    (1U << INDX_ADC_CR1_AWDSGL)

# define INDX_ADC_CR1_SCAN      8                     // Scan mode (interrupt on EOC of last channel)
# define MASK_ADC_CR1_SCAN      (1U << INDX_ADC_CR1_SCAN)

# define INDX_ADC_CR1_AWDIE     6                     // Analog watchdog interrupt enable
# define MASK_ADC_CR1_AWDIE     (1U << INDX_ADC_CR1_AWDIE)

# define INDX_ADC_CR1_EOCIE     5                     // End of conversion interrupt enable
# define MASK_ADC_CR1_EOCIE     (1U << INDX_ADC_CR1_EOCIE)

# define MASK_ADC_CR1_AWDCH     0x1F                  // Analog watchdog channel selection (0..17)

// CR2

# define INDX_ADC_CR2_TSVREFE   23                    // Temperature sensor and VREFINT enable (VREFINT == 1.2 V)

# define INDX_ADC_CR2_SWSTART   22                    // Start conversion of regular channels
# define MASK_ADC_CR2_SWSTART   (1U << INDX_ADC_CR2_SWSTART)

# define INDX_ADC_CR2_EXTTRIG   20                    // External trigger conversion mode for regular channels
# define MASK_ADC_CR2_EXTTRIG   (1U << INDX_ADC_CR2_EXTTRIG)

# define INDX_ADC_CR2_EXTSEL    17                    // External event select for regular group
# define MASK_ADC_CR2_EXTSEL_SWSTART (7U << INDX_ADC_CR2_EXTSEL)

# define INDX_ADC_CR2_DMA       8                     // Enable DMA
# define MASK_ADC_CR2_DMA       (1U << INDX_ADC_CR2_DMA)

# define INDX_ADC_CR2_CAL       2                     // starts A/D calibration
# define MASK_ADC_CR2_CAL       (1U << INDX_ADC_CR2_CAL)

# define INDX_ADC_CR2_CONT      1                     // Continuous conversion mode
# define MASK_ADC_CR2_CONT      (1U << INDX_ADC_CR2_CONT)
      
# define INDX_ADC_CR2_ADON      0                     // Enable ADC
# define MASK_ADC_CR2_ADON      (1U << INDX_ADC_CR2_ADON)

// SQR1

# define INDX_ADC_SQR1_L        20                    // Regular channel sequence length
# define MASK_ADC_SQR1_L        (0xFU << INDX_ADC_SQR1_L)        

#endif


























