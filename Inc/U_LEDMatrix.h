#include <HW_GPIO.h>
#include <Compiler.h>
#include <stdint.h>

#include <U_DrvSPI.h>



#define ANT_LEN 8U


typedef _GPIOConfig  AnTType[ANT_LEN];



void AnTInit(void);
void AnTOnAt(uint8_t index);
void AnTOffAt(uint8_t index);









