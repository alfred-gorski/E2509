#include <HW_GPIO.h>
#include <Compiler.h>
#include <stdint.h>

#include <U_DrvSPI.h>
#include <U_Queue.h>




#define COLUMN_LEN 8U
#define ROW_LEN 8U
typedef _GPIOConfig Column[COLUMN_LEN];
typedef uint8_t ImageData[ROW_LEN][COLUMN_LEN];


typedef struct{
	SPIHandle hSPI;
	const ImageData* data;
	Queue buffer;
}ChannelHandle;


typedef struct{
	ChannelHandle hChannelGn;
	ChannelHandle hChannelRd;
	Column hColumn;
}ImageHandle;




typedef enum {
	phase0 = 0, 
	phase1,
	phase2,
	phase3 
} Phase;


void ImageInit(ImageHandle *hImage);
void ScreenOn(ImageHandle *hImage);
void ImageOutEnOff(ImageHandle *hImage);













