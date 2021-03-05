#include <Compiler.h>

#include <HW_GPIO.h>
#include <HW_RCC.h>
#include <HW_SPI.h>

#include <U_DrvSPI.h>
#include <U_GPIOConfig.h>
#include <U_Queue.h>

/// SPI GPIO config data.
static const _SPIGPIOs SPIGPIOsGn = {
	{&GPIOA, 4}, {&GPIOA, 5}, {&GPIOA, 6}, {&GPIOA, 7}, {&GPIOC, 4},
};

static const _SPIGPIOs SPIGPIOsRd = {
	{&GPIOB, 12}, {&GPIOB, 13}, {&GPIOB, 14}, {&GPIOB, 15}, {&GPIOC, 6},
};

void SPIInit(SPIHandle *hSPI, Color color) {
  _SPIGPIOs gpios;

  switch (color) {
  case Gn:
    hSPI->instance = &SPI1;
    hSPI->gpios = SPIGPIOsGn;
    PeripheryEnable(RCC_SPI1);
    hSPI->color = Gn;
    break;
  case Rd:
    hSPI->instance = &SPI2;
    hSPI->gpios = SPIGPIOsRd;
    PeripheryEnable(RCC_SPI2);
    hSPI->color = Rd;
    break;
  }

  gpios = hSPI->gpios;

  GPIOConfig(gpios.latch, GPIO_O_STD_PP_02MHZ);
  GPIOConfig(gpios.clock, GPIO_O_ALT_PP_02MHZ);
  GPIOConfig(gpios.input, GPIO_I_FLOATING);
  GPIOConfig(gpios.output, GPIO_O_ALT_PP_02MHZ);
  GPIOConfig(gpios.outEn, GPIO_O_STD_PP_02MHZ);

  // configurate SPI registor
  hSPI->instance->CR1 |=
      (BaudRateScaler_8 << INDX_SPI_CR1_BR) // baudrate f_pclk/8
      | MASK_SPI_CR1_CPOL // second clock transition is the first data capture
                          // edge
      | MASK_SPI_CR1_SSM | MASK_SPI_CR1_SSI |
      MASK_SPI_CR1_MSTR; // master configuration

  hSPI->instance->CR1 |= MASK_SPI_CR1_SPE; // Enable
}

/// \brief send given data to SPI
int SPIEmit(SPIHandle *hSPI, uint32_t data) {
  uint8_t TxCount = 0;
  uint8_t TimeOutCount = 0;
  uint8_t pick = 0;

  hSPI->status = BUSY;

  while (TxCount < 4 && TimeOutCount < TIMEOUT_THRESHOLD) {
    if ((hSPI->instance->SR & MASK_SPI_SR_TXE) == MASK_SPI_SR_TXE) {
      pick = data & SIZE_8_MASK;
      data = data >> 8;
      hSPI->instance->DR = pick;
      TxCount++;
    } else {

      // Time out check
      TimeOutCount++;
      if (TimeOutCount == TIMEOUT_THRESHOLD) {
        hSPI->status = ERROR;
      }
    }
  }

  // Error check
  if (hSPI->status == BUSY) {
    hSPI->status = OK;
    return SUCCEED_SEND;
  } else {
    return ERROR_SEND;
  }
}

void SPILatch(SPIHandle *hSPI) {
  _GPIOConfig latch = hSPI->gpios.latch;
  setGPIOPin(latch);
  resetGPIOPin(latch);
}

void SPIOutEn(SPIHandle *hSPI) {
  _GPIOConfig outEn = hSPI->gpios.outEn;
  setGPIOPin(outEn);
}

void SPIOutEnOff(SPIHandle *hSPI) {
  _GPIOConfig outEn = hSPI->gpios.outEn;
  resetGPIOPin(outEn);
}
