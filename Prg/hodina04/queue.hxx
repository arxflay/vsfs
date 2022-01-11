// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#ifndef QUEUE_HXX
#define QUEUE_HXX

struct listNode
{
    listNode *next;
    void *value;
};

struct queue
{
    listNode *first;
    listNode *last;
    int count;
};

queue *createQueue();
void destroyQueue(queue *q);
bool isQueueEmpty(queue *q);
void enqueue(queue *q, void *value);
void *dequeue(queue *q);
void *front(queue *q);

#endif