#ifndef U_DrvSPI_H
#define U_DrvSPI_H

#include <Compiler.h>
#include <stdint.h>

#include <HW_GPIO.h>
#include <HW_SPI.h>

#include <U_GPIOConfig.h>

#define TIMEOUT_THRESHOLD 2000
#define SIZE_8_MASK (1 << 8) - 1

/** @enum Color
 *	@brief Channels
 */
typedef enum { Gn = 0, Rd } Color;

typedef enum { OK = 0, ERROR, BUSY } SPISendStatus;

/** @enum BaudRate
 * 	@brief baud rate scaler
 */
typedef enum {
  BaudRateScaler_2 = 0,
  BaudRateScaler_4,
  BaudRateScaler_8,
  BaudRateScaler_16,
  BaudRateScaler_32,
  BaudRateScaler_64,
  BaudRateScaler_128,
  BaudRateScaler_256
} BaudRate;

/** @struct _SPIGPIOs
 *  @brief Wrapper of all SPI GPIO PINs
 */
typedef struct {
  _GPIOConfig latch;
  _GPIOConfig clock;
  _GPIOConfig input;
  _GPIOConfig output;
  _GPIOConfig outEn;
} _SPIGPIOs;

typedef struct {
  RegisterBankSPI volatile *instance;
  _SPIGPIOs gpios;
  SPISendStatus status;
  Color color;
} SPIHandle;

void SPIInit(SPIHandle *const hSPI,const Color color);
int SPIEmit(SPIHandle *const hSPI, const uint32_t data);
void SPILatch(const SPIHandle *const hSPI);
void SPIOutEn(const SPIHandle *const hSPI);
void SPIOutEnOff(const SPIHandle *const hSPI);

#endif
