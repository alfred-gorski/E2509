#ifndef U_GPIOCONFIG_H
#define U_GPIOCONFIG_H

#include <HW_GPIO.h>




typedef struct{
	RegisterBankGPIO volatile *gpio;
	uint8_t pin;
}_GPIOConfig;



void GPIOConfig(_GPIOConfig gpioconfig, uint8_t value);

void setGPIOPin(_GPIOConfig gpioconfig);
void resetGPIOPin(_GPIOConfig gpioconfig);



#endif

