/**
 * @file 				U_Queue.c
 * @brief  	    Configurations of all used GPIO
 * @details     
 * @version 		1.0.0
 */


#include <U_Queue.h>
#include <stdint.h>

uint32_t len(const Queue *const hQueue);



void QueueInit(Queue *const hQueue) {
  hQueue->wcntr = 0;
  hQueue->rcntr = 0;
}


int isEmpty(const Queue *const hQueue) { 
	return len(hQueue) == 0; 
}


int isFull(const Queue *const hQueue) { 
	return len(hQueue) == QUEUE_CAPACITY; 
}


uint32_t pop(Queue *const hQueue) {
	return hQueue->buffer[hQueue->rcntr++ & QUEUE_MASK]; 
}


void push(Queue *const hQueue, uint32_t data) {
  hQueue->buffer[hQueue->wcntr++ & QUEUE_MASK] = data;
}


uint32_t len(const Queue *const hQueue) { 
	return hQueue->wcntr - hQueue->rcntr; 
}

void refill(Queue *const hQueue){
	hQueue->rcntr = 0;
}
