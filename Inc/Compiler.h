//
// Compiler.h
//

#if ! defined(__COMPILER_H__)
# define __COMPILER_H__

# if   defined(RELEASE) &&   defined(DEBUG)
#  error "You cannot define RELEASE and DEBUG at the same time"
# endif
# if ! defined(RELEASE) && ! defined(DEBUG)
#  error "You must define RELEASE or DEBUG!"
# endif

# if defined(__arm__)
#  include <stdint.h>
#  include <stdbool.h>

#  define BYTE                  uint8_t               ///< Byte-Datentyp (8 Bits).
#  define WORD                  uint32_t              ///< Wort-Datentyp (nach ARM-Konvention 32 Bits).
#  define HWRD                  uint16_t              ///< Halbwort-Datentyp (nach ARM-Konvention 16 Bits).

/// Nomenklatur <s>INT<nn>:
/// <s> = U bzw. S für unsigned bzw. signed
/// <nn> = 08, 12, 32, 64 für 8 bis 64 Bits

#  define UINT64                uint64_t
#  define SINT64                int64_t
#  define UINT32                uint32_t
#  define SINT32                int32_t
#  define UINT16                uint16_t
#  define SINT16                int16_t
#  define UINT08                uint8_t
#  define SINT08                int8_t
# else
#  error "Unknown Compiler"
# endif
#endif

