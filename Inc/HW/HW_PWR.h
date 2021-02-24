//
// HW_PWR.h
//

#ifndef __HW_PWR_H__
# define __HW_PWR_H__

# include <RB_PWR.h>

# include <Compiler.h>

/// Registerbank PWR ('RM0008 Reference manual' Abschnitt 4, 'Power control').
extern RegisterBankPWR volatile PWR;

/// Schreibschutz der Register der Backup-domain aktivieren.
void BackupDomainWriteProtectionOn (void);

/// Schreibschutz der Register der Backup-domain deaktivieren.
void BackupDomainWriteProtectionOff(void);

#endif

















































































