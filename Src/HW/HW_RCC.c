//
// HW_RCC.c
//

/// \file HW_RCC.c
/// Definition der RCC-Registerbank und der Funktionen, um den Takt einer Periphie ein- oder auszuschalten.

#include <HW_RCC.h>

RegisterBankRCC volatile RCC __attribute__((at(0x40021000)));

#define CHAN2REGINDEX(M)        ((M) >> 16)
#define CHAN2BITINDEX(M)        ((M) & 0xFFU)
#define CHAN2BITMASK(M)         (1U << CHAN2BITINDEX(M))

void PeripheryEnable(WORD const chanVal)
{
  RCC.clockCtrl.AxBENR[CHAN2REGINDEX(chanVal)] |=  CHAN2BITMASK(chanVal);
}

void PeripheryDisable(WORD const chanVal)
{
  RCC.clockCtrl.AxBENR[CHAN2REGINDEX(chanVal)] &= ~CHAN2BITMASK(chanVal);
}















































































