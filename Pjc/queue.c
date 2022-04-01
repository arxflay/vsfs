#include <stdlib.h>

#include "debug.h"
#include "queue.h"

queue *queue_create()
{
    linkedList *list = linkedList_create();
    queue *q = (queue*)calloc(1, sizeof(queue));
    check_mem(q);

    return q;

error:
    if(list)
        free(list);

    return NULL;
}

void *queue_dequeue(queue *q)
{
    return linkedList_shift(q->list);
}

void queue_enqueue(queue *q, void *value)
{
    linkedList_push(q->list, value);
}

int queue_count(queue *q)
{
    return linkedList_count(q->list);
}

void *queue_front(queue *q)
{
    return linkedList_front(q->list);
}

void queue_destroy(queue *q)
{
    if (q != NULL)
        linkedList_destroy(q->list);

    free(q);
}