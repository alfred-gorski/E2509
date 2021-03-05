/**
 * @file 				U_GPIOConfig.h
 * @brief  	    Configurations of all used GPIO
 * @details     use Configurations-Bits to initialize ,set or reset chosen GPIO
 * @version 		1.0.0
 */


#include <U_GPIOConfig.h>





 
 
 
 /// \brief use 4 Configurations-Bits to initialize the chose GPIO
void GPIOConfig(_GPIOConfig gpioconfig, uint8_t value){
	ConfigureGPIO(gpioconfig.gpio,gpioconfig.pin,value);
}



/// \brief set the output registor of the chosen GPIO to 1
void setGPIOPin(_GPIOConfig gpioconfig){
	gpioconfig.gpio->BSRR |= (1 << gpioconfig.pin);
}


/// \brief set the output registor of the chosen GPIO to 0
void resetGPIOPin(_GPIOConfig gpioconfig){
	gpioconfig.gpio->BRR |= (1 << gpioconfig.pin);
}

