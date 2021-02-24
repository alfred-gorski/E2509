//
// HW_TIM.c
//

/// \file HW_TIM.c
/// Definition aller Timer-Registerbänke.

#include <HW_TIM.H>

RegisterBankTIM volatile TIM1 __attribute__((at(0x40012C00)));
RegisterBankTIM volatile TIM2 __attribute__((at(0x40000000)));
RegisterBankTIM volatile TIM3 __attribute__((at(0x40000400)));
RegisterBankTIM volatile TIM4 __attribute__((at(0x40000800)));
RegisterBankTIM volatile TIM5 __attribute__((at(0x40000C00)));
































































































