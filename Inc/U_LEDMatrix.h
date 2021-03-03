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



*/

typedef struct{
	SPIHandle hSPI;
	uint8_t data[8][8];
	Queue buffer;
}ChannelHandle;


typedef struct{
	ChannelHandle hChannelGn;
	ChannelHandle hChannelRd;
}ImageHandle;


void AnTInit(void);
void AnTOnAt(uint8_t index);
void AnTOffAt(uint8_t index);

void ImageInit(ImageHandle *hImage);

void ChannelInitGn(ChannelHandle* hChannel);
void ChannelInitRd(ChannelHandle* hChannel);


void testScreenOn(ImageHandle *hImage);

void sentToBufferOnPhase(ChannelHandle* hChannel, Phase phase);
uint8_t getThreshold(Phase phase);



//void screenOn(ScreenHandle* hScreen, SPIHandle* hSPIGn,SPIHandle* hSPIRd);









