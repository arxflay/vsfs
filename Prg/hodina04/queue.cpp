// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include "queue.hxx"

queue *createQueue()
{
    queue *q{ new queue{} };
    q->first = nullptr;
    q->last = nullptr;
    q->count = 0;

    return q;
}

bool isQueueEmpty(queue *q)
{
    return (q->first == nullptr);
}

void enqueue(queue *q, void *value)
{
    if (q == nullptr)
        throw std::runtime_error("list null");

    listNode *node{ new listNode{} };
    node->next = nullptr;
    node->value = value;

    if (isQueueEmpty(q))
    {
        q->first = node;
        q->last = node;
    }
    else
    {
        q->last->next = node;
        q->last = node;
    }

    q->count++;
}

void *dequeue(queue *q)
{
    if (q == nullptr)
        throw std::runtime_error("list null");
    else if (isQueueEmpty(q))
        throw std::runtime_error("list is empty");

    void *value{ q->first->value };

    if (q->first->next == nullptr)
    {
        delete q->first;
        q->first = nullptr;
        q->last = nullptr;
    }
    else
    {
        listNode *newFirst{ q->first->next };
        delete q->first;
        q->first = newFirst;
    }

    q->count--;

    return value;
}

void *front(queue *q)
{
    if (q == nullptr)
        throw std::runtime_error("list null");
    else if (isQueueEmpty(q))
        throw std::runtime_error("list is empty");

    return q->first->value;
}

void destroyQueue(queue *q)
{
    if (q == nullptr)
        return;

    listNode *node{ q->first };

    while(node != nullptr)
    {
        listNode *next{ node->next };
        delete node;
        node = next;
    }

    delete q;
}