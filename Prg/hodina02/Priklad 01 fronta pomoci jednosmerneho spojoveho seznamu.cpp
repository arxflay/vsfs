// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <stdexcept>
#include <iostream>

struct listNode
{
    listNode *next;
    int value;
};

struct queue
{
    listNode *first;
    listNode *last;
};

queue *queueCreate()
{
    queue *q{ new queue{} };
    q->first = nullptr;
    q->last = nullptr;

    return q;
}

bool isEmpty(queue *q)
{
    return (q->first == nullptr);
}

void enqueue(queue *q, int value)
{
    if (q == nullptr)
        throw std::runtime_error("list null");

    listNode *node{ new listNode{} };
    node->next = nullptr;
    node->value = value;

    if (isEmpty(q))
    {
        q->first = node;
        q->last = node;
    }
    else
    {
        q->last->next = node;
        q->last = node;
    }
}

int dequeue(queue *q)
{
    if (q == nullptr)
        throw std::runtime_error("list null");
    else if (isEmpty(q))
        throw std::runtime_error("list is empty");

    int value{ q->first->value };

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

    return value;
}

int front(queue *q)
{
    if (q == nullptr)
        throw std::runtime_error("list null");
    else if (isEmpty(q))
        throw std::runtime_error("list is empty");

    return q->first->value;
}

void write(queue *q)
{
    if (q == nullptr)
        throw std::runtime_error("list null");
    else if (isEmpty(q))
        throw std::runtime_error("list is empty");

    listNode *node{ q->first };
    while (node != nullptr)
    {
        std::cout << node->value << ' ';
        node = node->next;
    }
    std::cout << '\n';
}

void queueDestroy(queue *q)
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

int main()
{
    queue *q{ queueCreate() };
    enqueue(q, 4); enqueue(q, 1); enqueue(q, 8);

    std::cout << dequeue(q) << ' ' << dequeue(q) << '\n';
    std::cout << "front: " << front(q) << '\n';
    std::cout << "isEmpty: " << std::boolalpha << isEmpty(q) << '\n';
    
    enqueue(q, 5); enqueue(q, 7);
    write(q);

    queueDestroy(q);

    return 0;
}