//
// HW_NVIC.c
//

/// \file HW_NVIC.c
/// Definition der NVIC- und SCB-Registerbänke und der Funktionen zur Konfiguration eines IRQs.

#include <HW_NVIC.h>

RegisterBankNVIC volatile NVIC __attribute__((at(0xE000E100)));
RegisterBankSCB  volatile SCB  __attribute__((at(0xE000ED00))); 

#define CHAN2REGINDEX(M)        ((M) >> 5)
#define CHAN2BITINDEX(M)        ((M) & 0x1F)
#define CHAN2BITMASK(M)         (1U << CHAN2BITINDEX(M))

void InterruptEnable(WORD const chan)
{
  NVIC.ISER[CHAN2REGINDEX(chan)] = CHAN2BITMASK(chan);
}

void InterruptDisable(WORD const chan)
{
  NVIC.ICER[CHAN2REGINDEX(chan)] = CHAN2BITMASK(chan);
}

void InterruptSetPrio(WORD const chan, BYTE const argPrio)
{
  NVIC.IPR.asByte[chan] = argPrio;
}











































































