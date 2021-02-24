//
// HW_RCC.h
//

/// \file HW_RCC.h
/// Deklaration der RCC-Registerbank und der Funktionen, um den Tak einer Periphie ein- oder auszuschalten.

#ifndef __HW_RCC_H__
# define __HW_RCC_H__

# include <RB_RCC.h>

extern RegisterBankRCC volatile RCC;

# define RCC_AHB                0x00000               ///< Teil der Peripheriekennnung, wenn Peripherie am AHB angeschlossen ist.
# define RCC_APB2               0x10000               ///< Teil der Peripheriekennnung, wenn Peripherie am APB2 angeschlossen ist.
# define RCC_APB1               0x20000               ///< Teil der Peripheriekennnung, wenn Peripherie am APB1 angeschlossen ist.

// Peripheriekennungen:

# define RCC_DMA1               (RCC_AHB  |  0) 
# define RCC_DMA2               (RCC_AHB  |  1)
# define RCC_ADC1               (RCC_APB2 |  9)
# define RCC_ADC2               (RCC_APB2 | 10)
# define RCC_TIM1               (RCC_APB2 | 11)
# define RCC_TIM2               (RCC_APB1 |  0)
# define RCC_TIM3               (RCC_APB1 |  1)
# define RCC_TIM4               (RCC_APB1 |  2)
# define RCC_TIM5               (RCC_APB1 |  3)
# define RCC_TIM6               (RCC_APB1 |  4)
# define RCC_TIM7               (RCC_APB1 |  5)
# define RCC_SPI1               (RCC_APB2 | 12) 
# define RCC_SPI2               (RCC_APB1 | 14) 
# define RCC_SPI3               (RCC_APB1 | 15)
# define RCC_USART1             (RCC_APB2 | 14)       ///< Peripheriekennung für USART1.
# define RCC_USART2             (RCC_APB1 | 17)
# define RCC_USART3             (RCC_APB1 | 18)
# define RCC_UART4              (RCC_APB1 | 19)
# define RCC_UART5              (RCC_APB1 | 20)
# define RCC_AFIO               (RCC_APB2 |  0)       ///< Peripheriekennung für AFIO (alternate function I/O, mapping der //O ports). 
# define RCC_GPIOA              (RCC_APB2 |  2)       ///< Peripheriekennung für GPIOA.
# define RCC_GPIOB              (RCC_APB2 |  3) 
# define RCC_GPIOC              (RCC_APB2 |  4) 
# define RCC_GPIOD              (RCC_APB2 |  5) 
# define RCC_GPIOE              (RCC_APB2 |  6) 
# define RCC_GPIOF              (RCC_APB2 |  7) 
# define RCC_GPIOG              (RCC_APB2 |  8) 
# define RCC_BKP                (RCC_APB1 | 27)
# define RCC_PWR                (RCC_APB1 | 28)
# define RCC_DAC                (RCC_APB1 | 29)

/// Takt einer Peripherie einschalten (erhöht die Leistungsaufnahme des Controllers).
/// Im der RCC-Registerbank befinden sich drei Register um den Takt der Peripherie ein- oder auszuschalten.
/// Jedes Bit dieser 32-Bit-Register ist einer Peripherie zugeordnet. Um den Peripherietakt einzuschalten, muss man also wissen, 
/// welches Bit in welchem Register zu setzen ist. Diese Information ist in der Peripheriekennung codiert.
/// Die 5 niederwertigsten Bits geben die Nummer des Bits an (0-relativ), die Bits 16 und 17 geben die Registernummer an (0 für AHB,
/// 1 für APB2 und 2 für APB1, je nachdem, über welchem Bus die Peripherie angeschlossen ist).
/// \param chan ist die zugehörige Peripheriekennung.
/// \note Diese Funktion \b muss vor der ersten Verwendung der entsprechenden Peripherie aufgerufen werden.
void PeripheryEnable (WORD chan);

/// Takt einer Peripherie ausschalten (reduziert die Leistungsaufnahme des Controllers).
/// \param chan ist die zugehörige Peripheriekennung.
/// \warning Nach aufruf dieser Funktion kann die entsprechende Peripherie nicht mehr verwendet werden.
void PeripheryDisable(WORD chan);

#endif


































