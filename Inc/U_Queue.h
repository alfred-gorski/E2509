#ifndef U_QUEUE_H
#define U_QUEUE_H

#include <stdint.h>

/** 
 *  @brief Queue's capacity
 *  @detail queue's capacity is set to 2^n
 */
#define QUEUE_LOG2_CAPACITY 5U
#define QUEUE_CAPACITY (1 << QUEUE_LOG2_CAPACITY)
#define QUEUE_MASK (QUEUE_CAPACITY - 1)

//
/** @struct Queue 
 *  @brief First-In-First-Out Queue implemented with Ring Buffer.
*/ 
typedef struct {
  unsigned wcntr;
  unsigned rcntr;
  uint32_t buffer[QUEUE_CAPACITY];
} Queue;

void QueueInit(Queue *const hQueue);
int isEmpty(const Queue *const hQueue);
int isFull(const Queue *const hQueue);
uint32_t pop(Queue *const hQueue);
void push(Queue *const hQueue, uint32_t data);
void refill(Queue *const hQueue);

#endif
