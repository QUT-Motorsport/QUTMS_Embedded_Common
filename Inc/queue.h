#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct message_queue {
    void *queue_items;
    size_t queue_item_size;
    size_t queue_length;
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} message_queue_t;

// initializes the queue
bool queue_init(message_queue_t *queue, size_t queue_item_size, size_t queue_length);

// frees queue memory and renders it unusable
bool queue_delete(message_queue_t *queue);

// clears all items in the queue (does not free memory)
bool queue_clear(message_queue_t *queue);

// adds a new item to the queue,
bool queue_add(message_queue_t *queue, void *item);

// gets the new item from the queue without removing it
bool queue_peek(message_queue_t *queue, void *peek);

// gets the next item from the queue and removes it
bool queue_next(message_queue_t *queue, void *item);

// is the queue currently full
bool queue_full(message_queue_t *queue);

// is the queue currently empty
bool queue_empty(message_queue_t *queue);

#endif
