#include <Compiler.h>
#include <stdint.h>

#include <HW_GPIO.h>

#include <U_DrvSPI.h>
#include <U_Queue.h>

#define COLUMN_LEN 8U
#define ROW_LEN 8U

/** @brief Column is wrapper of AnT GPIO
 */
typedef _GPIOConfig Column[COLUMN_LEN];

/** @brief ImageData
 *	@details 4 pixel data are encoded in 1 BYTE data. For each pixel, 0~3
 *	stands for brightness. e.g data 0xF0 encodes 100% 100% 0% 0%
 */
typedef uint8_t ImageData[ROW_LEN][COLUMN_LEN];

/** @struct ChannelHandle
 *	@brief carries a SPIHandle, ImageData and FIFO Queue.
 */
typedef struct {
  SPIHandle hSPI;
  const ImageData *data;
  Queue buffer;
} ChannelHandle;

/** @struct ImageHandle
 *	@brief carries Columns, Green and Red Channel.
 */
typedef struct {
  ChannelHandle hChannelGn;
  ChannelHandle hChannelRd;
  Column hColumn;
} ImageHandle;

/** @enum Phase
 *	@brief defines PWM Period. For a 4 level brightness screen, we have 0 ~
 *  3 Phases. 
 */
typedef enum { phase0 = 0, phase1, phase2, phase3 } Phase;

void ImageInit(ImageHandle *hImage);
void ScreenOn(ImageHandle *hImage);
void ImageOutEnOff(ImageHandle *hImage);
