// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <stdlib.h>
#include <time.h>

#include "debug.h"
#include "linkedlist.h"

linkedList *linkedList_create()
{
    linkedList *list = (linkedList*)calloc(1, sizeof(linkedList));
    check_mem(list)

    return list;

error:
    return NULL;
}

listNode *listNode_create(void *value)
{
    listNode *node = (listNode*)calloc(1, sizeof(listNode));
    check_mem(node)

    node->value = value;

    return node;
error:
    return NULL;
}

void linkedList_pushNode(linkedList *list, listNode *node)
{
    if (list == NULL || node == NULL)
        return;

    if (list->first == NULL)
        list->first = node;
    else
    {
        list->last->next = node;
        node->prev = list->last;
    }

    list->last = node;
    list->count++;
}

void linkedList_push(linkedList *list, void *value)
{
    if (list == NULL)
        return;

    listNode *node = listNode_create(value);
    linkedList_pushNode(list, node);
}

void linkedList_unshiftNode(linkedList *list, listNode *node)
{
    if (list == NULL || node == NULL)
        return;

    if (list->first == NULL)
        list->last = node;
    else
    {
        list->first->prev = node;
        node->next = list->first;
    }

    list->first = node;
    list->count++;
}

void linkedList_unshift(linkedList *list, void *value)
{
    if (list == NULL)
        return;
    
    listNode *node = listNode_create(value);
    linkedList_unshiftNode(list, node);
}

void *linkedList_shift(linkedList *list)
{
    if (list == NULL || list->count == 0)
        return NULL;

    void *value = list->first->value;
    listNode *oldFirst = list->first;

    if (oldFirst->next == NULL)
    {
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        list->first = oldFirst->next;
        list->first->prev = NULL;
    }

    free(oldFirst);

    list->count--;

    return value;
}

void *linkedList_pop(linkedList *list)
{
    if (list == NULL || list->count == 0)
        return NULL;
    
    void *value = list->last->value;
    listNode *oldLast = list->last;

    if (oldLast->prev == NULL)
    {
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        list->last = oldLast->prev;
        list->last->next = NULL;
    }

    free(oldLast);

    list->count--;

    return value;
}

void linkedList_destroy(linkedList *list)
{
    if (list != NULL)
    {
        listNode *node = list->first;

        while(node != NULL)
        {
            listNode *next = node->next;
            free(node);
            node = next;
        }

        free(list);
    }
}

void linkedList_removeNode(linkedList *list, listNode *node)
{
    if (node == list->first)
        linkedList_shift(list);
    else if (node == list->last)
        linkedList_pop(list);
    else
    {
        node->next->prev = node->prev;  
        node->prev->next = node->next;
            
        list->count--;

        free(node);
    }
}

void linkedList_swapNodes(linkedList *list, listNode *cur, listNode *next)
{
    if (cur == next)
        return;

    listNode *temp = NULL;

    if (next == list->last)
    {
        if (cur == list->first)
        {
            list->first = next;
            list->last = cur;
        }
        else
            list->last = cur;
    }
    else if (cur == list->first)
        list->first = next;

    if(cur->prev != NULL)
        cur->prev->next = next;
    if (next->prev != NULL)
        next->prev->next = cur;
    
    temp = cur->next;
    cur->next = next->next;
    next->next = temp;

    temp = cur->prev;
    cur->prev = next->prev;
    next->prev = temp;

    if(cur->next != NULL)
        cur->next->prev = cur;
    if(next->next != NULL)
        next->next->prev = next;
    
}

void linkedList_reverse(linkedList *list) 
{
    if (list == NULL || list->count <= 1)
        return;

    listNode *node = list->first;
    listNode *newNext = NULL;

    while(node != NULL)
    {
        listNode *next = node->next;
        node->prev = next;
        node->next = newNext;
        newNext = node;
        node = next;
    }

    node = list->first;
    list->first = list->last;
    list->last = node;
}

void linkedList_swapFirstLast(linkedList *list)
{
    if (list == NULL || list->count <= 1)
        return;

    linkedList_swapNodes(list, list->first, list->last);
}

void linkedList_swapSecondPenultimate(linkedList *list)
{
    if (list == NULL || list->count == 1 || list->count == 0)
        return;
    else if (list->count == 2)
    {
        linkedList_swapFirstLast(list);
        return;
    }

    listNode *second = list->first->next;
    listNode *penultimate = list->first;

    while(penultimate != NULL && penultimate->next != list->last)
        penultimate = penultimate->next;

    linkedList_swapNodes(list, second, penultimate);

}