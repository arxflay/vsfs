#include <stdlib.h>

#include "debug.h"
#include "stack.h"

stack *stack_create()
{
    linkedList *list = linkedList_create();
    stack *s = (stack*)calloc(1, sizeof(stack));
    check_mem(s);

    return s;

error:
    if(list)
        free(list);

    return NULL;
}

void *stack_pop(stack *st)
{
    return linkedList_pop(st->list);
}

void stack_push(stack *st, void *value)
{
    linkedList_push(st->list, value);
}

int stack_count(stack *st)
{
    return linkedList_count(st->list);
}

void *stack_peek(stack *st)
{
    return linkedList_peek(st->list);
}

void stack_destroy(stack *st)
{
    if (st != NULL)
        linkedList_destroy(st->list);

    free(st);
}