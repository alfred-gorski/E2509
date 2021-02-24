//
// HW_UART.c
//

/// \file HW_USART.c
/// Definition der USART/UART-Registerbänke.

#include <HW_USART.h>

RegisterBankUSART volatile USART1 __attribute__((at(0x40013800)));  ///< Registerbank für USART1.
RegisterBankUSART volatile USART2 __attribute__((at(0x40004400)));  ///< Registerbank für USART2.
RegisterBankUSART volatile USART3 __attribute__((at(0x40004800)));  ///< Registerbank für USART3.
RegisterBankUSART volatile UART4  __attribute__((at(0x40004C00)));  ///< Registerbank für UART4.
RegisterBankUSART volatile UART5  __attribute__((at(0x40005000)));  ///< Registerbank für UART5.



































































































