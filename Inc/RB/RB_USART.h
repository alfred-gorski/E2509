//
// RB_USART.h
//

/// \file RB_USART.h
/// Registerbank-Datentyp für USART/UART.

#ifndef __RB_USART_H__
# define __RB_USART_H__

# include <Compiler.h>

/// U(S)ART register bank.
/// STM32F103 Universal Synchronous/Asynchronous Receiver Transmitter (U(S)ARTx). See reference manual, chapter 25.
typedef struct __reg_bank_USART
{
  WORD SR;                                            ///< Status register.
  WORD DR;                                            ///< Data register.
  WORD BRR;                                           ///< Baud rate register.
  WORD CR1;                                           ///< Control register 1.
  WORD CR2;                                           ///< Control register 2.
  WORD CR3;                                           ///< Control register 3.
  WORD GTPR;                                          ///< Guard time and prescaler register.
} RegisterBankUSART;

// SR

# define INDX_USART_SR_PE       0U                    ///< parity error.
# define MASK_USART_SR_PE       (1U << INDX_USART_SR_PE)       

# define INDX_USART_SR_FE       1U                    ///< framing error.
# define MASK_USART_SR_FE       (1U << INDX_USART_SR_FE)

# define INDX_USART_SR_NE       2U                    ///< noise error.
# define MASK_USART_SR_NE       (1U << INDX_USART_SR_NE)

# define INDX_USART_SR_ORE      3U                    ///< overrun error.
# define MASK_USART_SR_ORE      (1U << INDX_USART_SR_ORE)

# define INDX_USART_SR_TC       6U                    ///< transmission complete.
# define MASK_USART_SR_TC       (1U << INDX_USART_SR_TC)
 
# define INDX_USART_SR_TXE      7U                    ///< write data register empty.
# define MASK_USART_SR_TXE      (1U << INDX_USART_SR_TXE)

# define INDX_USART_SR_RXNE     5U                    ///< read data register not empty.
# define MASK_USART_SR_RXNE     (1U << INDX_USART_SR_RXNE)

// CR1

# define INDX_USART_CR1_UE      13U                   // USART enable
# define MASK_USART_CR1_UE      (1U << INDX_USART_CR1_UE)

# define INDX_USART_CR1_TXEIE   7U                    // write data register empty interrupt enable
# define MASK_USART_CR1_TXEIE   (1U << INDX_USART_CR1_TXEIE)

# define INDX_USART_CR1_TCIE    6U                    // transmission complete interrupt enable
# define MASK_USART_CR1_TCIE    (1U << INDX_USART_CR1_TCIE)

# define INDX_USART_CR1_RXNEIE  5U                    // read data register not empty interrupt enable
# define MASK_USART_CR1_RXNEIE  (1U << INDX_USART_CR1_RXNEIE)

# define INDX_USART_CR1_TE      3U                    // transmitter enable
# define MASK_USART_CR1_TE      (1U << INDX_USART_CR1_TE)

# define INDX_USART_CR1_RE      2U                    // receiver enable
# define MASK_USART_CR1_RE      (1U << INDX_USART_CR1_RE)

// CR3

# define INDX_USART_CR3_CTSE    9
# define INDX_USART_CR3_RTSE    8

#endif
































