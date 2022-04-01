#ifndef STACK_H
#define STACK_H

#include "linkedlist.h"

typedef struct tagstack
{
    linkedList *list;
} stack;

stack *stack_create();
void stack_destroy(stack *s);

void *stack_dequeue(stack *s);
void stack_enqueue(stack *s, void *value);

int stack_count(stack *s);

void *stack_front(stack *s);

#endif
