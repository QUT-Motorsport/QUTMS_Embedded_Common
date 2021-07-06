#include "queue.h"

#include <string.h>

bool queue_init(message_queue_t *queue, size_t queue_item_size,
		size_t queue_length) {
	// assumes queue is an empty struct
	queue->queue_items = calloc(queue_length, queue_item_size);

	if (queue->queue_items == NULL) {
		// calloc failed
		return false;
	}

	queue->queue_item_size = queue_item_size;
	queue->queue_length = queue_length;

	queue->count = 0;
	queue->head = 0;
	queue->tail = queue->queue_length - 1;

	return true;
}

bool queue_delete(message_queue_t *queue) {
	if (queue == NULL) {
		return false;
	}

	// free queue memory
	if (queue->queue_items != NULL) {
		free(queue->queue_items);
		queue->queue_items = NULL;
	}

	return true;
}

bool queue_clear(message_queue_t *queue) {
	queue->count = 0;
	queue->head = 0;
	queue->tail =  queue->queue_length - 1;

	return true;
}

bool queue_add(message_queue_t *queue, void *item) {
	if (queue->count <  queue->queue_length) {
		queue->tail = (queue->tail + 1) %  queue->queue_length;
		memcpy(queue->queue_items + (queue->tail * queue->queue_item_size), item, queue->queue_item_size);
		queue->count++;

		return true;
	} else {
		// queue is full
		return false;
	}
}

bool queue_peek(message_queue_t *queue, void *peek) {
	if (queue->count > 0) {
		// copy next item into pointer
		memcpy(peek, queue->queue_items + (queue->head * queue->queue_item_size), queue->queue_item_size);
		return true;
	} else {
		return false;
	}
}

bool queue_next(message_queue_t *queue, void *next) {
	if (queue->count > 0) {
		// copy next item into pointer
		memcpy(next, queue->queue_items + (queue->head * queue->queue_item_size), queue->queue_item_size);

		// increase head pointer
		queue->head = (queue->head + 1) %  queue->queue_length;
		queue->count--;

		return true;
	} else {
		return false;
	}
}

bool queue_full(message_queue_t *queue) {
	return queue->count ==  queue->queue_length;
}

bool queue_empty(message_queue_t *queue) {
	return queue->count == 0;
}
