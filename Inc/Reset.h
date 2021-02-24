//
// Reset.h
//

#ifndef __RESET_H__
# define __RESET_H__

/// (Indirektes) Rücksetzen des Controllers via SVC.
/// \note Diese Funktion darf auch im nicht-privilegierten Modus aufgerufen werden.
/// \warning Diese Funktion darf nicht im SVC-Kontext aufgerufen werden, weil sie ihrerseits einen
/// SVC zur Ausführunf nutzt. Sie darf auch nicht im Kontext eines anderen IRQs aufgerufen werden, wenn dieser
/// die gleiche oder höhere Priorität als der SVC-IRQ hat.
__declspec(noreturn) 
void __svc(0) ResetController(void);

/// Direktes Rücksetzen des Controllers, indem ein spezieller Schlüssel in das AIRCR des SCB geschrieben wird
/// (vgl. Abschnitt 4.3.5, Application Interrupt and Reset Control Register, in Cortex-M3 Devices, Generic User Guide).
/// \warning Diese Funktion darf nur im privilegierten Modus aufgerufen werden.
__declspec(noreturn) 
void ResetController_privileged(void);

#endif






















































































