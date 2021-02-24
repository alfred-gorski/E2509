//
// RegBit.h
//

#ifndef __REGBIT_H__
# define __REGBIT_H__

# define REG_SET(N, REG)        ( (REG) |=   MASK_ ## N )
# define REG_RES(N, REG)        ( (REG) &= ~(MASK_ ## N))
# define REG_GET(N, REG)        (((REG) &   (MASK_ ## N)) != 0U)

// Namenskonvention für Register-Bits:
// INDX_<Bank>_<Reg>_<ID> = Nummer des Bits (0,1, ...)
// MASK_<Bank>_<Reg>_<ID> = Bit-Maske (== 1 << INDX_<Bank>_<Reg>_<ID>) 
// <Bank> = Register Bank, z.B. RCC
// <Reg> = Register Name, z.B. CR für Control Register
// <ID> = mnemonischer name des Bits, z.B. IE für Interrupt Enable

// schreibende Operationen
// SET_BIT(BANK, REG, ID) = Bit <ID> des Registers <REG> in der Bank <BANK> setzen
// RES_BIT(BANK, REG, ID) = Bit <ID> des Registers <REG> in der Bank <BANK> löschen

// lesende Operation
// GET_BIT(BANK, REG, ID) = Bit <ID> des Registers <REG> in der Bank <BANK> lesen

# define SET_BIT(BANK, REG, ID) REG_SET(BANK ## _ ## REG ## _ ## ID, BANK . REG)
# define RES_BIT(BANK, REG, ID) REG_RES(BANK ## _ ## REG ## _ ## ID, BANK . REG)
# define GET_BIT(BANK, REG, ID) REG_GET(BANK ## _ ## REG ## _ ## ID, BANK . REG)
#endif
























































































