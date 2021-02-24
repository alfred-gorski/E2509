//
// STM32F10xxx.h
//

#ifndef __STM32F10XXX_H__
# define __STM32F10XXX_H__

# include <Compiler.h>

// Spezielle Controller-Funktionen.
// Der Controller STM32F10xx von ST beinhaltet neben dem Cortex-M3-Core eigene Erweiterungen. In diesem Namensraum werden Funktionen zur Verfügung gestellt, 
// um den Controller zu initialisieren bzw. wichtige Informationen anzurufen.
// (bzgl. der Taktfrequenzen s. Abschnitt 6, "Low-, medium- and high-density reset and clock control (RCC)" des Reference Manual)

/// Hauptinitialisierung der STM32F10xxx-Register.
void STM32F10xxx_Config(void);

/// Systemtakt.
/// \return Es wird der Systemtakt (SYSCLK) in Hz zurückgegeben.
unsigned STM32F10xxx_GetSysClk(void);

/// AHB oder HCLK-Takt.
/// \return HCLK = SYSCLK / AHB-Pre-scaler (1, 2, ... 512)
unsigned STM32F10xxx_GetHClk(void);                          

unsigned STM32F10xxx_GetAHB_Prescaler_Shift(void);

unsigned STM32F10xxx_GetAPB1_Prescaler_Shift(void);

/// PCLK1-Takt.
/// \return Clock of the low speed domain (APB1), HCLK / APB1-Pre-scaler
unsigned STM32F10xxx_GetAPB1_Clock(void);

unsigned STM32F10xxx_GetAPB2_Prescaler_Shift(void);

/// PCLK2-Takt.
/// \return Clock of the high speed domain (APB2), HCLK / APB2-Pre-scaler
unsigned STM32F10xxx_GetAPB2_Clock(void);

#endif






























































