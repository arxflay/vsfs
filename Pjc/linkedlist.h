#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>

typedef struct taglistNode listNode;

struct taglistNode
{
    listNode *prev;
    listNode *next;
    void *value;
};

typedef struct tagLinkedList
{
    listNode *first;
    listNode *last;
    size_t count;
} linkedList;

#define linkedList_front(list) ((list)->first)
#define linkedList_peek(list) ((list)->last)
#define linkedList_count(list) ((list)->count)

linkedList *linkedList_create();
listNode *listNode_create(void *value);
void linkedList_destroy(linkedList *list);

void linkedList_pushNode(linkedList *list, listNode *node);
void linkedList_push(linkedList *list, void *value);

void linkedList_unshiftNode(linkedList *list, listNode *node);
void linkedList_unshift(linkedList *list, void *value);

void *linkedList_shift(linkedList *list);
void *linkedList_pop(linkedList *list);

void linkedList_removeNode(linkedList *list, listNode *node);
void linkedList_swapNodes(linkedList *list, listNode *cur, listNode *next);
void linkedList_reverse(linkedList *list);
void linkedList_swapFirstLast(linkedList *list);
void linkedList_swapSecondPenultimate(linkedList *list);

#endif