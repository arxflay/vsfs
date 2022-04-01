#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist.h"

typedef struct tagqueue
{
    linkedList *list;
} queue;

queue *queue_create();
void queue_destroy(queue *q);

void *queue_dequeue(queue *q);
void queue_enqueue(queue *q, void *value);

int queue_count(queue *q);

void *queue_front(queue *q);

#endif
