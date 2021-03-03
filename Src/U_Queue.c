#include <U_Queue.h>



unsigned len(const Queue *const hQueue);

void QueueInit(Queue *const hQueue) {
  hQueue->wcntr = 0;
  hQueue->rcntr = 0;
}

int isEmpty(const Queue *const hQueue) { return len(hQueue) == 0; }

int isFull(const Queue *const hQueue) { return len(hQueue) == QUEUE_CAPACITY; }

// TODO: ERRO Handling
uint32_t pop(Queue *const hQueue) { return hQueue->buffer[hQueue->rcntr++ & QUEUE_MASK]; }
// TODO: ERRO Handling
void push(Queue *const hQueue, uint32_t data) {
  hQueue->buffer[hQueue->wcntr++ & QUEUE_MASK] = data;
}

unsigned len(const Queue *const hQueue) { return hQueue->wcntr - hQueue->rcntr; }
