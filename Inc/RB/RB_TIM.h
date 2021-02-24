//
// RB_TIM.h
//

/// \file RB_TIM.h
/// Registerbank-Datentyp für Timer.

#ifndef __RB_TIM_H__
# define __RB_TIM_H__

# include <Compiler.H>

/// TIM register bank.
/// STM32F103 TIMer (TIMx). Siehe "Reference manual", Kapitel 13 - 15
typedef struct __reg_bank_TIM
{
  WORD CR1;                                           ///< Control register 1.
  WORD CR2;                                           ///< Control register 2.
  WORD SMCR;                                          ///< Slave mode control register (NOT for basic timer TIM6 & TIM7).
  WORD DIER;                                          ///< DMA/interrupt enable register.
  WORD SR;                                            ///< Status register.
  WORD EGR;                                           ///< Event generation register.

  HWRD CCMR1;                                         ///< Capture/Compare mode register 1 (NOT for basic timer TIM6 & TIM7).
  HWRD reserved1;
  HWRD CCMR2;                                         ///< Capture/Compare mode register 2 (NOT for basic timer TIM6 & TIM7).
  HWRD reserved2;
  WORD CCER;                                          ///< Capture/Compare enable register (NOT for basic timer TIM6 & TIM7).
  WORD CNT;                                           ///< Counter.
  WORD PSC;                                           ///< Prescaler.
  WORD ARR;                                           ///< Auto-reload register.
  WORD RCR;                                           ///< Repetition count register (TIM1 & TIM8 only).
  WORD CCR[4];                                        ///< Capture/Compare register 1 .. 4  (NOT for basic timer TIM6 & TIM7).
  WORD BDTR;                                          ///< Break and dead time register (TIM1 & TIM8 only).
  WORD DCR;                                           ///< DMA control register (NOT for basic timer TIM6 & TIM7).
  WORD DMAR;                                          ///< DMA address for full transfer (NOT for basic timer TIM6 & TIM7).
} RegisterBankTIM;

// CR1

# define INDX_TIM_CR1_CEN       0                     // 1 = counter enable
# define MASK_TIM_CR1_CEN       (1U << INDX_TIM_CR1_CEN)       

# define INDX_TIM_CR1_URS       2 
# define MASK_TIM_CR1_URS       (1U << INDX_TIM_CR1_URS)       

# define INDX_TIM_CR1_OPM       3                     // one pulse mode, 1 = counter stops counting at the next update event (clearing CEN)
# define MASK_TIM_CR1_OPM       (1U << INDX_TIM_CR1_OPM)

# define INDX_TIM_CR1_DIR       4                     // count direction, 1 = down, 0 = up
# define MASK_TIM_CR1_DIR       (1U << INDX_TIM_CR1_DIR)       

# define INDX_TIM_CR1_ARPE      7
# define MASK_TIM_CR1_ARPE      (1U << INDX_TIM_CR1_ARPE)

# define INDX_TIM_CR1_CKD       8                     // clock division for dead time and sampling clock
# define MASK_TIM_CR1_CKD_1     (0U << INDX_TIM_CR1_CKD)
# define MASK_TIM_CR1_CKD_2     (1U << INDX_TIM_CR1_CKD)
# define MASK_TIM_CR1_CKD_4     (2U << INDX_TIM_CR1_CKD)

// CR2

# define INDX_TIM_CR2_MMS       4
# define MASK_TIM_CR2_MMS       (7U << INDX_TIM_CR2_MMS)
# define MASK_TIM_CR2_MMS_UPDATE (2U << INDX_TIM_CR2_MMS)

// SMCR

# define INDX_TIM_SMCR_SMS      0                     // slave mode selection
# define MASK_TIM_SMCR_SMS      (0x7U << INDX_TIM_SMCR_SMS)
# define MASK_TIM_SMCR_SMS_DISABLED (0x0U << INDX_TIM_SMCR_SMS) // prescaler is clocked directly by internal clock CK_PSC
# define MASK_TIM_SMCR_SMS_EXTCLOCK (0x7U << INDX_TIM_SMCR_SMS) // rising edges of the selected trigger (TRGI) clock the counter
# define MASK_TIM_SMCR_SMS_RESET_MODE (0x4U << INDX_TIM_SMCR_SMS)

# define INDX_TIM_SMCR_TS       4                     // trigger selection
# define MASK_TIM_SMCR_TS       (7U << INDX_TIM_SMCR_TS)
# define MASK_TIM_SMCR_TS_ITR0  (0U << INDX_TIM_SMCR_TS)
# define MASK_TIM_SMCR_TS_ITR1  (1U << INDX_TIM_SMCR_TS)
# define MASK_TIM_SMCR_TS_ITR2  (2U << INDX_TIM_SMCR_TS)
# define MASK_TIM_SMCR_TS_ITR3  (3U << INDX_TIM_SMCR_TS)

// DIER

# define INDX_TIM_DIER_UIE      0
# define MASK_TIM_DIER_UIE      (1U << INDX_TIM_DIER_UIE)

# define INDX_TIM_DIER_CC1IE    1
# define MASK_TIM_DIER_CC1IE    (1U << INDX_TIM_DIER_CC1IE)

# define INDX_TIM_DIER_CC2IE    2
# define MASK_TIM_DIER_CC2IE    (1U << INDX_TIM_DIER_CC2IE)

# define INDX_TIM_DIER_CC3IE    3
# define MASK_TIM_DIER_CC3IE    (1U << INDX_TIM_DIER_CC3IE)

# define INDX_TIM_DIER_CC4IE    4
# define MASK_TIM_DIER_CC4IE    (1U << INDX_TIM_DIER_CC4IE)

// SR

# define INDX_TIM_SR_UIF        0
# define MASK_TIM_SR_UIF        (1U << INDX_TIM_SR_UIF)

# define INDX_TIM_SR_CC1IF      1
# define MASK_TIM_SR_CC1IF      (1U << INDX_TIM_SR_CC1IF)

# define INDX_TIM_SR_CC2IF      2
# define MASK_TIM_SR_CC2IF      (1U << INDX_TIM_SR_CC2IF)

# define INDX_TIM_SR_CC3IF      3
# define MASK_TIM_SR_CC3IF      (1U << INDX_TIM_SR_CC3IF)

# define INDX_TIM_SR_CC4IF      4
# define MASK_TIM_SR_CC4IF      (1U << INDX_TIM_SR_CC4IF)

# define MASK_TIM_SR_CCxIF      (MASK_TIM_SR_CC1IF | MASK_TIM_SR_CC2IF | MASK_TIM_SR_CC3IF | MASK_TIM_SR_CC4IF)

# define INDX_TIM_SR_TIF        6
# define MASK_TIM_SR_TIF        (1U << INDX_TIM_SR_TIF)

// CCMR

# define INDX_TIM_CCMR_CCxS     0
# define MASK_TIM_CCMR_CCxS_TIx (1U << INDX_TIM_CCMR_CCxS)

# define INDX_TIM_CCMR_ICxF     4
# define MASK_TIM_CCMR_ICxF_2   (1U << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_4   (2U << INDX_TIM_CCMR_ICxF)
# define MASK_TIM_CCMR_ICxF_8   (3U << INDX_TIM_CCMR_ICxF)

# define INDX_TIM_CCMR_OCxM     4                     // output compare mode
# define MASK_TIM_CCMR_OCxM     (0x7U << INDX_TIM_CCMR_OCxM)     
# define MASK_TIM_CCMR_OCxM_FROZEN (0x0U << INDX_TIM_CCMR_OCxM)     
# define MASK_TIM_CCMR_OCxM_PWM1 (0x6U << INDX_TIM_CCMR_OCxM)     
# define MASK_TIM_CCMR_OCxM_PWM2 (0x7U << INDX_TIM_CCMR_OCxM)     

# define INDX_TIM_CCMR_OCxPE    3                     // output compare preload enable: 1 = preload register CCRx enabled. Read/Write operations access 
                                                      // the preload register. CCRx preload value is loaded in the active register at each update event.
# define MASK_TIM_CCMR_OCxPE    (1U << INDX_TIM_CCMR_OCxPE)

// CCER

# define INDX_TIM_CCER_CC1E     0
# define INDX_TIM_CCER_CC1P     1

# define INDX_TIM_CCER_CC2E     4
# define INDX_TIM_CCER_CC2P     5

# define INDX_TIM_CCER_CC3E     8
# define MASK_TIM_CCER_CC3E     (1U << INDX_TIM_CCER_CC3E)

# define INDX_TIM_CCER_CC3P     9

# define INDX_TIM_CCER_CC3NE    10
# define MASK_TIM_CCER_CC3NE    (1U << INDX_TIM_CCER_CC3NE)

# define INDX_TIM_CCER_CC4E     12
# define MASK_TIM_CCER_CC4E     (1U << INDX_TIM_CCER_CC4E)

# define INDX_TIM_CCER_CC4P     13

// BDTR

# define INDX_TIM_BDTR_MOE      15                    // main output enable 
# define MASK_TIM_BDTR_MOE      (1U << INDX_TIM_BDTR_MOE)

# define INDX_TIM_BDTR_AOE      14                    // automatic output enable (MOE=1 on next update event)
# define MASK_TIM_BDTR_AOE      (1U << INDX_TIM_BDTR_AOE)      

# define INDX_TIM_BDTR_LOCK     8
# define MASK_TIM_BDTR_LOCK     (1U << INDX_TIM_BDTR_LOCK)

#endif
