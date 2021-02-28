#include "U_Queue.h"



unsigned len(const Queue *const p);

void init(Queue *const p) {
  p->wcntr = 0;
  p->rcntr = 0;
}

int isEmpty(const Queue *const p) { return len(p) == 0; }

int isFull(const Queue *const p) { return len(p) == QUEUE_CAPACITY; }

// TODO: ERRO Handling
uint32_t pop(Queue *const p) { return p->buffer[p->rcntr++ & QUEUE_MASK]; }
// TODO: ERRO Handling
void push(Queue *const p, uint32_t data) {
  p->buffer[p->wcntr++ & QUEUE_MASK] = data;
}

unsigned len(const Queue *const p) { return p->wcntr - p->rcntr; }
