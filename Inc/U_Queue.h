#ifndef U_QUEUE_H
#define U_QUEUE_H

#include <stdint.h>
#include <stdio.h>


#define QUEUE_LOG2_CAPACITY 5U
#define QUEUE_CAPACITY (1 << QUEUE_LOG2_CAPACITY)
#define QUEUE_MASK (QUEUE_CAPACITY - 1)


// first-in-first-out Queue implemented with Ring Buffer
typedef struct {
  unsigned wcntr;
  unsigned rcntr;
  uint32_t buffer[QUEUE_CAPACITY];
} Queue;

void init(Queue *const p);
int isEmpty(const Queue *const p);
int isFull(const Queue *const p);
uint32_t pop(Queue *const p);
void push(Queue *const p, uint32_t data);




#endif
