#include <U_GPIOConfig.h>




void GPIOConfig(_GPIOConfig gpioconfig, uint8_t value){
	ConfigureGPIO(gpioconfig.gpio,gpioconfig.pin,value);
}



void setGPIOPin(_GPIOConfig gpioconfig){
	gpioconfig.gpio->BSRR |= (1 << gpioconfig.pin);
}



void resetGPIOPin(_GPIOConfig gpioconfig){
	gpioconfig.gpio->BRR |= (1 << gpioconfig.pin);
}

