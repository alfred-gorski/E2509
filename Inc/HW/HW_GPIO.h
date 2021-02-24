//
// HW_GPIO.h
//

/// \file HW_GPIO.h
/// Deklaration aller GPIO-Registerbänke und der Helper-Funktion, zur Einstellung des GPIO-Modus (input, output, alternate function).

#ifndef __HW_GPIO_H__
# define __HW_GPIO_H__

# include <RB_GPIO.h>

extern RegisterBankGPIO volatile GPIOA;               ///< GPIOA-Registerbank.
extern RegisterBankGPIO volatile GPIOB;               ///< GPIOB-Registerbank.
extern RegisterBankGPIO volatile GPIOC;               ///< GPIOC-Registerbank.
extern RegisterBankGPIO volatile GPIOD;               ///< GPIOD-Registerbank.
extern RegisterBankGPIO volatile GPIOE;               ///< GPIOE-Registerbank.
extern RegisterBankGPIO volatile GPIOF;               ///< GPIOF-Registerbank.
extern RegisterBankGPIO volatile GPIOG;               ///< GPIOG-Registerbank.

# define GPIO_I_ANALOG          0x00U                 ///< Configuration bitmask: Analog input.
# define GPIO_I_FLOATING        0x04U                 ///< Configuration bitmask: Floating (digital) input.
# define GPIO_I_PD              0x08U                 ///< Configuration bitmask: Input with pull-down resistor.
# define GPIO_I_pu              0x10U
# define GPIO_I_PU              (GPIO_I_PD | GPIO_I_pu) ///< Configuration bitmask: Input with pull-up resistor.

# define GPIO_O_OD              0x04                  ///< Configuration bitmask: Open-drain output stage.
# define GPIO_O_ALT             0x08                  ///< Configuration bitmask: Alternate I/O.

// PP == push-pull, OD == open drain
// STD == standard I/O, ALT == alternate I/O

# define GPIO_O_STD_PP_10MHZ    0x01U
# define GPIO_O_STD_OD_10MHZ    (GPIO_O_STD_PP_10MHZ | GPIO_O_OD)
# define GPIO_O_ALT_PP_10MHZ    (GPIO_O_STD_PP_10MHZ | GPIO_O_ALT)
# define GPIO_O_ALT_OD_10MHZ    (GPIO_O_ALT_PP_10MHZ | GPIO_O_OD)

# define GPIO_O_STD_PP_02MHZ    0x02U                 ///< Configuration bitmask: General purpose output, push-pull output stage,  2 MHz bandwidth.
# define GPIO_O_STD_OD_02MHZ    (GPIO_O_STD_PP_02MHZ | GPIO_O_OD)       ///< Configuration bitmask: General purpose output, open-drain output stage,  2 MHz bandwidth.
# define GPIO_O_ALT_PP_02MHZ    (GPIO_O_STD_PP_02MHZ | GPIO_O_ALT)      ///< Configuration bitmask: Alternate output, push-pull output stage,  2 MHz bandwidth.
# define GPIO_O_ALT_OD_02MHZ    (GPIO_O_ALT_PP_02MHZ | GPIO_O_OD)       ///< Configuration bitmask: Alternate output, open-drain output stage,  2 MHz bandwidth.

# define GPIO_O_STD_PP_50MHZ    0x03U
# define GPIO_O_STD_OD_50MHZ    (GPIO_O_STD_PP_50MHZ | GPIO_O_OD)
# define GPIO_O_ALT_PP_50MHZ    (GPIO_O_STD_PP_50MHZ | GPIO_O_ALT)
# define GPIO_O_ALT_OD_50MHZ    (GPIO_O_ALT_PP_50MHZ | GPIO_O_OD)

/// Helper function to setup I/O-Pin für input or output.
/// \param rb points to the GPIO register bank.
/// \param pin is the pin number (from 0 to 15).
/// \param config is the configuration bitmask (i.e. GPIO_I_FLOATING or GPIO_O_ALT_PP_02MHZ).
/// \warning The pin number must be in the range from 0 to 15. If the pin number is greater 15 the result is unpredictable!
void ConfigureGPIO(RegisterBankGPIO volatile * rb, unsigned pin, WORD config);

#endif
