//
// HW_PWR.c
//

#include <HW_PWR.h>

RegisterBankPWR volatile PWR __attribute__((at(0x40007000)));

#include <RegBit.h>

void BackupDomainWriteProtectionOn (void) { RES_BIT(PWR, CR, DBP); }
void BackupDomainWriteProtectionOff(void) { SET_BIT(PWR, CR, DBP); }

























































































