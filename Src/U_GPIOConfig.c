#include <U_GPIOConfig.h>

/// \brief set GPIO PIN to value
void GPIOConfig(_GPIOConfig gpioconfig, uint8_t value) {
  ConfigureGPIO(gpioconfig.gpio, gpioconfig.pin, value);
}

/// \brief set GPIO PIN output on
void setGPIOPin(_GPIOConfig gpioconfig) {
  gpioconfig.gpio->BSRR |= (1 << gpioconfig.pin);
}

/// \brief sset GPIO PIN output off
void resetGPIOPin(_GPIOConfig gpioconfig) {
  gpioconfig.gpio->BRR |= (1 << gpioconfig.pin);
}
