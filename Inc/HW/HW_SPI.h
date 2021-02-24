//
// HW_SPI.h
//

/// \file HW_SPI.h
/// Deklaration aller SPI-Registerbänke.

#ifndef __HW_SPI_H__
# define __HW_SPI_H__

# include <RB_SPI.h>

extern RegisterBankSPI volatile SPI1;                 ///< SPI1-Registerbank.
extern RegisterBankSPI volatile SPI2;                 ///< SPI2-Registerbank.

// Anmerkung: SPI3-Registerbank wird nicht verwednet, da deren I/O-Pins mit den JTAG-Pins identisch sind.

#endif


















































































