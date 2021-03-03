#include <HW_GPIO.h>
#include <Compiler.h>
#include <stdint.h>

#include <U_DrvSPI.h>
#include <U_Queue.h>



#define ANT_LEN 8U


typedef _GPIOConfig  AnTType[ANT_LEN];


typedef enum {
	phase0 = 0, 
	phase1,
	phase2,
	phase3 
} Phase;



/*
typedef struct uint8_t Image[8][8];



typedef struct{
	Queue buffer;
	Image* image;
}ImageHandle;


typedef struct{
	ImageHandle *hImageGn;
	ImageHandle *hImageRd;
}ScreenHandle;

*/

typedef struct{
	SPIHandle hSPI;
	uint8_t data[8][8];
	Queue buffer;
}ChannelHandle;




void AnTInit(void);
void AnTOnAt(uint8_t index);
void AnTOffAt(uint8_t index);



void ChannelInitGn(ChannelHandle* hChannel);
void ChannelInitRd(ChannelHandle* hChannel);
void screenOn(ChannelHandle* hChannelGn, ChannelHandle *hChannelRd);

void sentToBufferOnPhase(ChannelHandle* hChannel, Phase phase);
uint8_t getThreshold(Phase phase);



//void screenOn(ScreenHandle* hScreen, SPIHandle* hSPIGn,SPIHandle* hSPIRd);









