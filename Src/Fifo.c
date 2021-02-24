/// \file Fifo.c
/// Funktionen und Strukturen zur Verwendung eines Byte-FIFOs (Implementierung).

#include <Fifo.h>

void InitFifo(FifoType volatile * const p)
{
  p->wcntr = 0U;
  p->rcntr = 0U;
}

bool IsFifoEmpty(FifoType volatile const * const p) { return GetFifoNumberOfItems(p) ==                0U; }
bool IsFifoFull (FifoType volatile const * const p) { return GetFifoNumberOfItems(p) == FIFO_ARRAY_LENGTH; }

BYTE FifoRemove(FifoType volatile * const p)                  
{ 
  ASSERT(! IsFifoEmpty(p)); 
  
  return p->buffer[p->rcntr++ & FIFO_ARRAY_MASK];        
}

void FifoInsert(FifoType volatile * const p, BYTE const data) 
{ 
  ASSERT(! IsFifoFull (p));        
  
  p->buffer[p->wcntr++ & FIFO_ARRAY_MASK] = data; 
}


