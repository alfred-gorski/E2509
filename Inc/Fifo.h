/// \file Fifo.h
/// Funktionen und Strukturen zur Verwendung eines Byte-FIFOs.

#if ! defined(guard_FIFO_H)
# define guard_FIFO_H

# include <Compiler.h>
# include <Debug.h>

# if ! defined(FIFO_ARRAY_LOG2LEN)       
#  define FIFO_ARRAY_LOG2LEN    4U
# endif

# define FIFO_ARRAY_LENGTH      (1U << FIFO_ARRAY_LOG2LEN)
# define FIFO_ARRAY_MASK        (FIFO_ARRAY_LENGTH - 1U)

typedef struct __Fifo
{
  unsigned wcntr;
  unsigned rcntr;
  BYTE buffer[FIFO_ARRAY_LENGTH];
} FifoType;

void InitFifo(FifoType volatile * p);

__inline unsigned GetFifoNumberOfItems(FifoType volatile const * const p)
{
  return p->wcntr - p->rcntr;
}

bool IsFifoEmpty(FifoType volatile const * p);

bool IsFifoFull (FifoType volatile const * p);

BYTE FifoRemove(FifoType volatile * p);                  

void FifoInsert(FifoType volatile * p, BYTE data);

#endif
