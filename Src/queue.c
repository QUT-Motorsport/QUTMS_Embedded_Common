#include "queue.h"
#include <stdlib.h>

bool queue_init(message_queue_t *queue, size_t queue_item_size,
		size_t queue_length) {
	// assumes queue is an empty struct
	queue->queue_items = calloc(queue_item_size, queue_length);

	if (queue->queue_items == NULL) {
		// calloc failed
		return false;
	}

	queue->count = 0;
	queue->head = 0;
	queue->tail = QUEUE_LENGTH - 1;

	queue->queue_item_size = queue_item_size;
	queue->queue_length = queue_length;
}

bool queue_delete(message_queue_t *queue) {
	if (queue == NULL) {
		return true;
	}
	if (queue->queue_items != NULL) {
		free(queue->queue_items);
		queue->queue - items = NULL;
	}

	return true;
}

int queue_clear(message_queue_t *queue) {
	queue->count = 0;
	queue->head = 0;
	queue->tail = QUEUE_LENGTH - 1;

	return 0;
}

int queue_add(message_queue_t *queue, CAN_t *msg) {
	if (queue->count < QUEUE_LENGTH) {
		queue->tail = (queue->tail + 1) % QUEUE_LENGTH;
		queue->queue[queue->tail] = *msg;
		queue->count++;

		return 0;
	} else {
		// queue is full
		return -1;
	}
}

int queue_peek(message_queue_t *queue, CAN_t *peek) {
	if (queue->count > 0) {
		*peek = queue->queue[queue->head];
		return 0;
	} else {
		return -1;
	}
}

int queue_next(message_queue_t *queue, CAN_t *next) {
	if (queue->count > 0) {
		*next = queue->queue[queue->head];
		queue->head = (queue->head + 1) % QUEUE_LENGTH;
		queue->count--;
		return 0;
	} else {
		return -1;
	}
}

bool queue_full(message_queue_t *queue) {
	return queue->count == QUEUE_LENGTH;
}

bool queue_empty(message_queue_t *queue) {
	return queue->count == 0;
}
