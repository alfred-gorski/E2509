//
// HW_NVIC.h
//

/// \file HW_NVIC.h
/// Deklaration der NVIC- und SCB-Registerbänke und der Funktionen zur Konfiguration eines IRQs.

#if ! defined(__HW_NVIC_H__)
# define __HW_NVIC_H__

# include <RB_NVIC.h>

extern RegisterBankNVIC volatile NVIC;                ///< Registerbank für NVIC.
extern RegisterBankSCB volatile SCB;                  ///< Registerbank für SCB (System Control Block).

# define NVIC_WWDG               0               
# define NVIC_PVD                1              
# define NVIC_RTC                3
# define NVIC_FLASH              4
# define NVIC_RCC                5
# define NVIC_EXTI00             6
# define NVIC_EXTI01             7
# define NVIC_EXTI02             8
# define NVIC_EXTI03             9   
# define NVIC_EXTI04            10  
# define NVIC_DMA1_CHAN1        11
# define NVIC_DMA1_CHAN2        12
# define NVIC_DMA1_CHAN3        13   
# define NVIC_DMA1_CHAN4        14   
# define NVIC_DMA1_CHAN5        15
# define NVIC_DMA1_CHAN6        16 
# define NVIC_DMA1_CHAN7        17   
# define NVIC_ADC1_2            18  
# define NVIC_EXTI05_09         23  
# define NVIC_TIM1_BRK          24  
# define NVIC_TIM1_UP           25 
# define NVIC_TIM1_TRG_COM      26
# define NVIC_TIM1_CC           27   
# define NVIC_TIM2              28
# define NVIC_TIM3              29
# define NVIC_TIM4              30
# define NVIC_SPI1              35
# define NVIC_SPI2              36
# define NVIC_USART1            37  
# define NVIC_USART2            38  
# define NVIC_USART3            39
# define NVIC_EXTI10_15         40 
# define NVIC_RTCALARM          41
# define NVIC_SPI3              51
# define NVIC_UART4             52
# define NVIC_UART5             53   

/// Externen Interrupt freischalten.
/// \param chan ist die IRQ-Nummer.
void InterruptEnable (WORD chan);

/// Externen Interrupt sperren.
/// \param chan ist die IRQ-Nummer.
void InterruptDisable(WORD chan);

/// Priorität eines externen Interrupts einstellen.
/// \param chan ist die IRQ-Nummer.
/// \param argPrio gint die Priorität an  (0 = höchste Priorität, 255 = niedrigste Priorität), jedoch d
void InterruptSetPrio(WORD chan, BYTE argPrio);

# define INTERRUPT_ENABLE(M)    InterruptEnable(NVIC_ ## M)
# define INTERRUPT_DISABLE(M)   InterruptDisable(NVIC_ ## M)
# define INTERRUPT_PRIO(M, P)   InterruptSetPrio(NVIC_ ## M, P)
#endif








































