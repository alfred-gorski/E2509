#include <HW_GPIO.h>
#include <Compiler.h>
#include <stdint.h>

#include <U_DrvSPI.h>



#define ANT_LEN 8U


typedef _GPIOConfig  AnTType[ANT_LEN];



void AnTInit(void);




void screenOn(SPIHandle* hSPIGn,SPIHandle* hSPIRd);









