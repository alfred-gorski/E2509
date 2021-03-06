#include <Compiler.h>
#include <string.h>

#include <U_DrvSPI.h>
#include <U_DrvTimer.h>
#include <U_GPIOConfig.h>
#include <U_LEDMatrix.h>
#include <U_Queue.h>

/// colSwitch is setted by Timer2 when LED matrix should light next column.
uint8_t volatile colSwitch = 0;
/// imageSwitch is setted by Timer3 when LED matrix should show next image.
uint8_t volatile imageSwitch = 0;

/// prevImage is a intermediate variable help know if imageSwitch changed.
uint8_t prevImage = 0;

/// cur describes the current column index. we use bit operation, mask to
/// simulate a 3 bit counter
uint32_t cur = 0;

void LEDOnAtCol(const ImageHandle *hImage,const uint8_t index);
void LEDOffAtCol(const ImageHandle *hImage,const uint8_t index);

void ImageOutEn(const ImageHandle *const hImage);
void ColDataSend(ImageHandle *const hImage);
void ImageLatch(const ImageHandle *const hImage);

void ChannelInit(ChannelHandle *hChannel, const Color color);
void BufferFill(ChannelHandle *const hChannel);
void BufferRefill(ChannelHandle *const hChannel);
void sentToBufferOnPhase(ChannelHandle *const hChannel,const Phase phase);
uint8_t Threshold(const Phase phase);

void ImageReinit(ImageHandle *hImage,const int image);

uint8_t getCur(void);
uint8_t getPre(void);

static const ImageData dataGn = {
    255, 255, 170, 170, 85,  85,  0,   0,   255, 255, 170, 170, 85,
    85,  0,   0,   255, 255, 170, 170, 85,  85,  0,   0,   255, 255,
    170, 170, 85,  85,  0,   0,   0,   0,   85,  85,  170, 170, 255,
    255, 0,   0,   85,  85,  170, 170, 255, 255, 0,   0,   85,  85,
    170, 170, 255, 255, 0,   0,   85,  85,  170, 170, 255, 255};

static const ImageData dataRd = {
    250, 250, 250, 250, 250, 250, 250, 250, 80,  80,  80,  80,  80,
    80,  80,  80,  5,   5,   5,   5,   5,   5,   5,   5,   175, 175,
    175, 175, 175, 175, 175, 175, 250, 250, 250, 250, 250, 250, 250,
    250, 80,  80,  80,  80,  80,  80,  80,  80,  5,   5,   5,   5,
    5,   5,   5,   5,   175, 175, 175, 175, 175, 175, 175, 175};

static const Column columnConfig = {
    {&GPIOA, 12}, // antr1
    {&GPIOA, 11}, // antr2
    {&GPIOA, 10}, // antr3
    {&GPIOA, 9},  // antr4
    {&GPIOA, 8},  // antr5
    {&GPIOC, 9},  // antr6
    {&GPIOC, 8},  // antr7
    {&GPIOC, 7},  // antr8
};

/** @brief the main controll function.
 */
void ScreenOn(ImageHandle *const hImage) {
  if (isEmpty(&hImage->hChannelGn.buffer)) {
    if (imageSwitch != prevImage) {
      prevImage = imageSwitch;
      ImageReinit(hImage, prevImage);
    } else {
      BufferRefill(&hImage->hChannelGn);
      BufferRefill(&hImage->hChannelRd);
    }
  }

  if (colSwitch == 1) {
    colSwitch = 0;

    ImageOutEnOff(hImage);
    ColDataSend(hImage);
    ImageLatch(hImage);
    ImageOutEn(hImage);

    LEDOffAtCol(hImage, getPre());
    LEDOnAtCol(hImage, getCur());

    cur++;
  }
}

void ImageInit(ImageHandle *const hImage) {
  int i = 0;
  ChannelInit(&hImage->hChannelGn, Gn);
  ChannelInit(&hImage->hChannelRd, Rd);
  memcpy(hImage->hColumn, columnConfig, sizeof(columnConfig));

  for (i = 0; i < COLUMN_LEN; i++) {
    GPIOConfig(hImage->hColumn[i], GPIO_O_STD_PP_02MHZ);
    LEDOffAtCol(hImage, i);
  }
  BufferFill(&hImage->hChannelGn);
  BufferFill(&hImage->hChannelRd);
}

uint8_t getCur(void) { return cur & ((1 << 3) - 1); }

uint8_t getPre(void) { return (cur - 1) & ((1 << 3) - 1); }

void ImageReinit(ImageHandle *const hImage, const int image) {
  QueueInit(&hImage->hChannelGn.buffer);
  QueueInit(&hImage->hChannelRd.buffer);
  switch (image) {
  case 0:
    hImage->hChannelGn.data = &dataGn;
    hImage->hChannelRd.data = &dataRd;
    break;
  case 1:
    hImage->hChannelGn.data = &dataRd;
    hImage->hChannelRd.data = &dataGn;
    break;
  }
  BufferFill(&hImage->hChannelGn);
  BufferFill(&hImage->hChannelRd);
}

void LEDOnAtCol(const ImageHandle *const hImage, const uint8_t index) {
  resetGPIOPin(hImage->hColumn[index]);
}

void LEDOffAtCol(const ImageHandle *const hImage,const  uint8_t index) {
  setGPIOPin(hImage->hColumn[index]);
}

void ImageOutEn(const ImageHandle *const hImage) {
  SPIOutEn(&hImage->hChannelGn.hSPI);
  SPIOutEn(&hImage->hChannelRd.hSPI);
}

void ImageOutEnOff(const ImageHandle *const hImage) {
  SPIOutEnOff(&hImage->hChannelGn.hSPI);
  SPIOutEnOff(&hImage->hChannelRd.hSPI);
}

void ColDataSend(ImageHandle *const hImage) {
  SPIEmit(&hImage->hChannelGn.hSPI, pop(&hImage->hChannelGn.buffer));
  SPIEmit(&hImage->hChannelRd.hSPI, pop(&hImage->hChannelRd.buffer));
}

void ImageLatch(const ImageHandle *const hImage) {
  SPILatch(&hImage->hChannelGn.hSPI);
  SPILatch(&hImage->hChannelRd.hSPI);
}

void ChannelInit(ChannelHandle *const hChannel, const Color color) {

  SPIInit(&hChannel->hSPI, color);
  QueueInit(&hChannel->buffer);
  switch (color) {
  case Gn:
    hChannel->data = &dataGn;
    break;
  case Rd:
    hChannel->data = &dataRd;
    break;
  }
}

void BufferRefill(ChannelHandle *const hChannel) { refill(&hChannel->buffer); }


void BufferFill(ChannelHandle *const hChannel) {
  sentToBufferOnPhase(hChannel, phase0);
  sentToBufferOnPhase(hChannel, phase1);
  sentToBufferOnPhase(hChannel, phase2);
  sentToBufferOnPhase(hChannel, phase3);
}

void sentToBufferOnPhase(ChannelHandle *hChannel, const Phase phase) {
  uint32_t data = 0;
  uint32_t flag = 0;
  size_t col;
  size_t row;
  size_t j;

  uint8_t threshold = Threshold(phase);
	//TODO: Not CPU Cache friendly, need to change ImageData definition.
  for (col = 0; col < COLUMN_LEN; col++) {
    for (row = 0; row < ROW_LEN; row++) {
      for (j = 0; j < 4; j++) {
        flag = (((*hChannel->data)[row][col] & ((1 << (8 - j * 2)) - 1)) >>
                (6 - j * 2)) >= threshold;
        data = (data << 1) + flag;
      }
    }
    push(&hChannel->buffer, data);
    data = 0;
  }
}


uint8_t Threshold(const Phase phase) {
  uint8_t threshold = 0;
  switch (phase) {
  case phase0:
    threshold = 1;
    break;
  case phase1:
    threshold = 2;
    break;
  case phase2:
    threshold = 3;
    break;
  case phase3:
    threshold = 3;
    break;
  }
  return threshold;
}
