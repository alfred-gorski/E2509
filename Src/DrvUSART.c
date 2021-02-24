//
// DrvUSART.c
//

#include <HW_RCC.h>
#include <HW_GPIO.h>
#include <HW_USART.h>
#include <HW_NVIC.h>

#include <DrvUSART.h>

#include <Fifo.h>

#include <Debug.h>

#include <STM32F10xxx.h>

typedef unsigned (* CalcClockFncType)(void);

typedef struct
{
  WORD rccUsart;
  WORD rccGpio;
  unsigned txPin; 
  unsigned rxPin; 
  //unsigned perClock;
  CalcClockFncType calcClockfnc;
  RegisterBankUSART volatile  * rbUsart;
  RegisterBankGPIO volatile * rbGpio;
  WORD irqNum;
} UsartConfigType;

struct __UsartContext
{
  FifoType recv;
  FifoType send;
  unsigned overruns;
  UsartConfigType const * config;
};

#define INIT_CONFIG(U, G, TX, RX, CF) { RCC_USART ## U, RCC_GPIO ## G, TX, RX, CF, &USART ## U, &GPIO ## G, NVIC_USART ## U }

static UsartContextType volatile usart1Context;
static UsartContextType volatile usart2Context;
static UsartContextType volatile usart3Context;

static UsartContextType volatile * FindContext(UsartPortType const port)
{
  switch(port)
  {
    default        :
    case usartPort1: return &usart1Context;
    case usartPort2: return &usart2Context;
    case usartPort3: return &usart3Context;
  }
}

static UsartConfigType const * FindConfig(UsartPortType const port)
{
  static UsartConfigType const usart1Config = INIT_CONFIG(1, A,  9U, 11U, STM32F10xxx_GetAPB2_Clock);
  static UsartConfigType const usart2Config = INIT_CONFIG(2, A,  2U,  3U, STM32F10xxx_GetAPB1_Clock);
  static UsartConfigType const usart3Config = INIT_CONFIG(3, B, 10U, 11U, STM32F10xxx_GetAPB1_Clock);

  switch(port)
  {
    default        :
    case usartPort1: return &usart1Config;
    case usartPort2: return &usart2Config;
    case usartPort3: return &usart3Config;
  }
}

UsartResultType InitUsart(UsartPortType const port, unsigned const baudRate, UsartHandleType * handle)
{
  if ( baudRate >= USART_BAUD_RATE_MIN && baudRate <= USART_BAUD_RATE_MAX )
  {
    UsartContextType volatile * const context = FindContext(port);
    UsartConfigType const * const config = FindConfig(port);
    
    InitFifo(&context->recv);
    InitFifo(&context->send);
    context->overruns = 0U;
    context->config = config;
    
    PeripheryEnable(config->rccUsart);
    PeripheryEnable(config->rccGpio);
    ConfigureGPIO(config->rbGpio, config->txPin, GPIO_O_ALT_PP_02MHZ);
    ConfigureGPIO(config->rbGpio, config->rxPin, GPIO_I_FLOATING);

    config->rbUsart->CR1 = MASK_USART_CR1_UE;
    config->rbUsart->BRR = (*config->calcClockfnc)() / baudRate;
    config->rbUsart->CR1 = MASK_USART_CR1_UE | MASK_USART_CR1_TE | MASK_USART_CR1_RE | MASK_USART_CR1_RXNEIE;
    
    InterruptEnable(config->irqNum);
    
    *handle = context;
    
    return usartSuccess;
  } else
    return usartInvBaudRate;
}

UsartResultType UsartSend(UsartHandleType const handle, BYTE const data)
{
  UsartContextType volatile * const context = handle;
  FifoType volatile * const fifo = &context->send;
  UsartConfigType const * const config = context->config;
  RegisterBankUSART volatile * const usart = config->rbUsart;
  UsartResultType result;
  
  if ( ! IsFifoFull(fifo) )
  {
    FifoInsert(fifo, data);
    
    result = usartSuccess;
  } else
    result = usartCantSend;
    
  usart->CR1 |= MASK_USART_CR1_TXEIE;

  return result;  
}

UsartResultType UsartRecv(UsartHandleType const handle, BYTE * const buffer)
{
  UsartContextType volatile * const context = handle;
  FifoType volatile * const fifo = &context->recv;

  if ( ! IsFifoEmpty(fifo) )
  {
    *buffer = FifoRemove(fifo);    

    return usartSuccess;
  } else
    return usartNoData;
}

static void Interrupt(UsartContextType volatile * const context)
{
  UsartConfigType const * const config = context->config;
  RegisterBankUSART volatile * const usart = config->rbUsart;
  
  if ( (usart->SR & MASK_USART_SR_TXE ) != 0U )
  {
    FifoType volatile * const fifo = &context->send;
    
    if ( IsFifoEmpty(fifo) )
    {
      usart->CR1 &= ~MASK_USART_CR1_TXEIE;
    } else
    {
      usart->DR = FifoRemove(fifo); 
    }
  }
  
  if ( (usart->SR & MASK_USART_SR_RXNE) != 0U )
  {
    FifoType volatile * const fifo = &context->recv;
    BYTE const data = usart->DR;
    
    if ( IsFifoFull(fifo) )
    {
      context->overruns++;
    } else
    {
      FifoInsert(fifo, data);
    }
  }
}

void IRQ_USART1(void) { Interrupt(&usart1Context); }
void IRQ_USART2(void) { Interrupt(&usart2Context); }
void IRQ_USART3(void) { Interrupt(&usart3Context); }
