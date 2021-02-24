//
// Reset.h
//

#include <Reset.h>
#include <Debug.h>

#include <HW_NVIC.h>

#define RELEASE_CODE            0x05FA0000U           // Magic number defined by core, must be written to AIRCR to unlock

__declspec(noreturn) 
void ResetController_privileged(void)
{
  DEBUG_PUTS(__FUNCTION__);
  // force a controller reset by writing a reset sequence to AIRCR of SCB

  SCB.AIRCR = RELEASE_CODE | 0x04U;           
}
