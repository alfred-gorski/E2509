//
// RW_RCC.h
//

/// \file RB_RCC.h
/// Registerbank-Datentyp für RCC.

#ifndef __RB_RCC_H__
# define __RB_RCC_H__

# include <Compiler.h>

/// RCC register bank.
/// STM32F103 Reset and Clock Control (RCC). See reference manual, chapter 6 and 7
typedef struct __reg_bank_RCC
{
  WORD CR;                                            ///< Control register.
  WORD CFGR;                                          ///< Configuration register.
  WORD CIR;                                           ///< Clock interrupt register.
  WORD APBRSTR[2];                                    ///< APB2/1 peripheral reset register.

  /// Control periphery enable register(s) type.
  union RCCCtrlType {
    struct {
      WORD AHPENR;  
      WORD APB2ENR;  
      WORD APB1ENR;  
    } allRegs;    
    WORD AxBENR[3];    
  } clockCtrl;                                        ///< APBENR/AHB2ENR/AHB1ENR peripheral clock enable registers.
  WORD BDCR;                                          ///< Backup domain control register.
  WORD CSR;                                           ///< Control/status register.
} RegisterBankRCC;

// CR

# define INDX_RCC_CR_HSION      0
# define MASK_RCC_CR_HSION      (1U <<  INDX_RCC_CR_HSION)

# define INDX_RCC_CR_HSIRDY     1
# define MASK_RCC_CR_HSIRDY     (1U << INDX_RCC_CR_HSIRDY)

# define INDX_RCC_CR_HSEON      16
# define MASK_RCC_CR_HSEON      (1U << INDX_RCC_CR_HSEON)

# define INDX_RCC_CR_PPRE1      8
# define MASK_RCC_CR_PPRE1_02   (0x4U << INDX_RCC_CR_PPRE1)
# define MASK_RCC_CR_PPRE1_04   (0x5U << INDX_RCC_CR_PPRE1)
# define MASK_RCC_CR_PPRE1_08   (0x6U << INDX_RCC_CR_PPRE1)
# define MASK_RCC_CR_PPRE1_16   (0x7U << INDX_RCC_CR_PPRE1)
# define MASK_RCC_CR_PPRE1      MASK_RCC_CR_PPRE1_16

# define INDX_RCC_CR_PPRE2      11
# define MASK_RCC_CR_PPRE2_02   (0x4U << INDX_RCC_CR_PPRE2)
# define MASK_RCC_CR_PPRE2_04   (0x5U << INDX_RCC_CR_PPRE2)
# define MASK_RCC_CR_PPRE2_08   (0x6U << INDX_RCC_CR_PPRE2)
# define MASK_RCC_CR_PPRE2_16   (0x7U << INDX_RCC_CR_PPRE2)
# define MASK_RCC_CR_PPRE2      MASK_RCC_CR_PPRE2_16

# define INDX_RCC_CR_HSERDY     17
# define MASK_RCC_CR_HSERDY     (1U << INDX_RCC_CR_HSERDY)    

# define INDX_RCC_CR_PLL1ON     24
# define MASK_RCC_CR_PLL1ON     (1U << INDX_RCC_CR_PLL1ON)

# define INDX_RCC_CR_PLL1RDY    25
# define MASK_RCC_CR_PLL1RDY    (1U << INDX_RCC_CR_PLL1RDY)

# define INDX_RCC_CR_PLL2ON     26                    // connectivity line devices only
# define MASK_RCC_CR_PLL2ON     (1U << INDX_RCC_CR_PLL2ON)

# define INDX_RCC_CR_PLL2RDY    27                    // connectivity line devices only
# define MASK_RCC_CR_PLL2RDY    (1U << INDX_RCC_CR_PLL2RDY)

# define INDX_RCC_CR_PLL3ON     28                    // connectivity line devices only
# define MASK_RCC_CR_PLL3ON     (1U << INDX_RCC_CR_PLL3ON)

# define INDX_RCC_CR_PLL3RDY    29                    // connectivity line devices only
# define MASK_RCC_CR_PLL3RDY    (1U << INDX_RCC_CR_PLL3RDY)

// CFGR

# define MASK_RCC_CFGR_SW_HSI   0x0U                  // system clock = HSI
# define MASK_RCC_CFGR_SW_HSE   0x1U                  // system clock = HSE
# define MASK_RCC_CFGR_SW_PLL   0x2U                  // system clock = PLL
# define MASK_RCC_CFGR_SW       0x3U

# define MASK_RCC_CFGR_SWS      (MASK_RCC_CFGR_SW << 2)  // SW status 

# define MASK_RCC_CFGR_HPRE     0xF0U                 // AHB prescaler 
# define MASK_RCC_CFGR_HPRE_002 0x80U                 // AHB prescaler   2
# define MASK_RCC_CFGR_HPRE_004 0x90U                 // AHB prescaler   4
# define MASK_RCC_CFGR_HPRE_008 0xA0U                 // AHB prescaler   8 
# define MASK_RCC_CFGR_HPRE_016 0xB0U                 // AHB prescaler  16
# define MASK_RCC_CFGR_HPRE_064 0xC0U                 // AHB prescaler  64
# define MASK_RCC_CFGR_HPRE_128 0xD0U                 // AHB prescaler 128
# define MASK_RCC_CFGR_HPRE_256 0xE0U                 // AHB prescaler 256
# define MASK_RCC_CFGR_HPRE_512 0xF0U                 // AHB prescaler 512

# define INDX_RCC_CFGR_PLLSRC   16                    
# define MASK_RCC_CFGR_PLLSRC   (1U << INDX_RCC_CFGR_PLLSRC)

# define INDX_RCC_CFGR_PLLXTPRE 17
# define MASK_RCC_CFGR_PLLXTPRE (1U << INDX_RCC_CFGR_PLLXTPRE)

# define INDX_RCC_CFGR_PLLMUL   18
# define MASK_RCC_CFGR_PLLMUL_02 (0x0U << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_03 (0x1U << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_04 (0x2U << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_05 (0x3U << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_06 (0x4U << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_07 (0x5U << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_08 (0x6U << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_09 (0x7U << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_10 (0x8U << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_11 (0x9U << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_12 (0xAU << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_13 (0xBU << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_65 (0xBU << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_14 (0xCU << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_15 (0xDU << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL_16 (0xEU << INDX_RCC_CFGR_PLLMUL)
# define MASK_RCC_CFGR_PLLMUL   (0xFU << INDX_RCC_CFGR_PLLMUL)

# define INDX_RCC_CFGR2_PREDIV1 0
# define MASK_RCC_CFGR2_PREDIV1 (0xFU << INDX_RCC_CFGR2_PREDIV1)

# define INDX_RCC_CFGR2_PREDIV2 4
# define MASK_RCC_CFGR2_PREDIV2 (0xFU << INDX_RCC_CFGR2_PREDIV2)

# define INDX_RCC_CFGR2_PLL2MUL 8
# define MASK_RCC_CFGR2_PLL2MUL_08 (0x6U << INDX_RCC_CFGR2_PLL2MUL)
# define MASK_RCC_CFGR2_PLL2MUL_09 (0x7U << INDX_RCC_CFGR2_PLL2MUL)
# define MASK_RCC_CFGR2_PLL2MUL_10 (0x8U << INDX_RCC_CFGR2_PLL2MUL)
# define MASK_RCC_CFGR2_PLL2MUL_11 (0x9U << INDX_RCC_CFGR2_PLL2MUL)
# define MASK_RCC_CFGR2_PLL2MUL_12 (0xAU << INDX_RCC_CFGR2_PLL2MUL)
# define MASK_RCC_CFGR2_PLL2MUL_13 (0xBU << INDX_RCC_CFGR2_PLL2MUL)
# define MASK_RCC_CFGR2_PLL2MUL_14 (0xCU << INDX_RCC_CFGR2_PLL2MUL)
# define MASK_RCC_CFGR2_PLL2MUL_16 (0xEU << INDX_RCC_CFGR2_PLL2MUL)
# define MASK_RCC_CFGR2_PLL2MUL_20 (0xFU << INDX_RCC_CFGR2_PLL2MUL)
# define MASK_RCC_CFGR2_PLL2MUL (0xFU << INDX_RCC_CFGR2_PLL2MUL)

# define INDX_RCC_CFGR2_PREDIV1SRC 16
# define MASK_RCC_CFGR2_PREDIV1SRC (1U << INDX_RCC_CFGR2_PREDIV1SRC)

// BDCR

# define INDX_RCC_BDCR_LSEON    0
# define MASK_RCC_BDCR_LSEON    (1U << INDX_RCC_BDCR_LSEON)

# define INDX_RCC_BDCR_LSERDY   1
# define MASK_RCC_BDCR_LSERDY   (1U << INDX_RCC_BDCR_LSERDY)

# define MASK_RCC_BDCR_RTCSEL   0x00000300U
# define MASK_RCC_BDCR_RTCSEL_LSE 0x00000100U
# define MASK_RCC_BDCR_RTCSEL_LSI 0x00000200U
# define MASK_RCC_BDCR_RTCSEL_HSE_DIV_128 0x00000300U

# define INDX_RCC_BDCR_RTCEN    15
# define MASK_RCC_BDCR_RTCEN    (1U << INDX_RCC_BDCR_RTCEN)

# define INDX_RCC_BDCR_BDRST    16
# define MASK_RCC_BDCR_BDRST    (1U << INDX_RCC_BDCR_BDRST)

// CSR

# define INDX_RCC_CSR_LSION     0
# define MASK_RCC_CSR_LSION     (1U << INDX_RCC_CSR_LSION)

# define INDX_RCC_CSR_LSIRDY    1
# define MASK_RCC_CSR_LSIRDY    (1U << INDX_RCC_CSR_LSIRDY)

#endif 
