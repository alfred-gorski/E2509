#include <HW_GPIO.h>
#include <Compiler.h>
#include <stdint.h>

#include <U_DrvSPI.h>
#include <U_Queue.h>



#define ANT_LEN 8U


typedef _GPIOConfig  AnTType[ANT_LEN];

typedef struct uint8_t Image[8][8];

typedef enum {
	phase0 = 0, 
	phase1,
	phase2,
	phase3 
} Phase;

typedef struct{
	Queue buffer;
	Image* image;
}ImageHandle;

typedef struct{
	ImageHandle *hImageGn;
	ImageHandle *hImageRd;
}ScreenHandle;

void AnTInit(void);




void screenOn(ScreenHandle* hScreen, SPIHandle* hSPIGn,SPIHandle* hSPIRd);









