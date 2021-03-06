#ifndef U_GPIOCONFIG_H
#define U_GPIOCONFIG_H

#include <HW_GPIO.h>
#include <stdint.h>

/** @struct _GPIOConfig
 *	@brief Wrapper of GPIO PIN
 */
typedef struct {
  RegisterBankGPIO volatile *gpio;
  uint8_t pin;
} _GPIOConfig;

void GPIOConfig(const _GPIOConfig gpioconfig, const uint8_t value);
void setGPIOPin(const _GPIOConfig gpioconfig);
void resetGPIOPin(const _GPIOConfig gpioconfig);

#endif
