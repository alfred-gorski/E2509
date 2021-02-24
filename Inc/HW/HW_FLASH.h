//
// HW_FLASH.h
//

/// \file HW_FLASH.h
/// Deklaration der FLASH-Registerbank und der Option-Bytes.

#ifndef __HW_FLASH_H__
# define __HW_FLASH_H__

# include <RB_FLASH.h>

extern RegisterBankFLASH volatile FLASH;              ///< FLASH-Registerbank.

#ifndef NO_OPT
# define NUM_OF_OPTION_BYTES    8
# define FLASH_READUNPROT       0xA5

/// Datentyp zur Implementierung der Options-Bytes.
typedef union 
{
  BYTE asByte[NUM_OF_OPTION_BYTES * sizeof(HWRD)];
  HWRD asHWrd[NUM_OF_OPTION_BYTES];
} OBArray;

extern OBArray const volatile OB;                     ///< Option-Bytes (spezielle Bytes, die das Verhalten des Controllers steuern).

# endif
#endif








































































