// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <stdexcept>
#include <iostream>
#include "doublylinkedlist.hxx"

doublyLinkedList *doublyLinkedListCreate()
{
    doublyLinkedList *list{ new doublyLinkedList{} };
    list->first = nullptr;
    list->last = nullptr;
    list->count = 0;

    return list;
}

void pushNode(doublyLinkedList *list, listNode *node)
{
    if (list->first == nullptr)
    {
        list->first = node;
        list->last = node;
    }
    else
    {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;
}

void push(doublyLinkedList *list, int value)
{
    listNode *node { new listNode{} };
    node->next = nullptr;
    node->value = value;

    pushNode(list, node);
}

int shift(doublyLinkedList *list)
{
    if (list->first == nullptr)
        throw std::runtime_error("list is empty");

    int value{ list->first->value };

    if (list->first->next == nullptr)
    {
        delete list->first;
        list->first = nullptr;
        list->last = nullptr;
    }
    else
    {
        listNode *newFirst { list->first->next };
        delete list->first;
        list->first = newFirst;
        newFirst->prev = nullptr;
    }

    list->count--;

    return value;
}

doublyLinkedList *convertArray(int *array, int length)
{
    doublyLinkedList *list{ doublyLinkedListCreate() };
    for (int i{ 0 }; i < length; i++)
        push(list, array[i]);

    return list;
}

void doublyLinkedListDestroy(doublyLinkedList *list)
{
    if (list != nullptr)
    {
        listNode *node{ list->first };
        while(node != nullptr)
        {
            listNode *next{ node->next };
            delete node;
            node = next;
        }

        delete list;
    }
}

std::ostream& operator<< (std::ostream& out, doublyLinkedList *list) //only for testing
{
    listNode *node{ list->first };
    while(node != nullptr)
    {
        out << node->value << ' ';
        node = node->next;
    }

    return out;
}

void removeNode(doublyLinkedList *list, listNode *node)
{
    if (node == list->first)
        shift(list);
    else
    {
        if (node->next == nullptr)
            list->last = node->prev;
        else
            node->next->prev = node->prev;
        
        if (node->prev != nullptr)
            node->prev->next = node->next;
            
        list->count--;

        delete node;

    }
}

void swapNodes(doublyLinkedList *list, listNode *cur, listNode *next)
{
    listNode *temp{ nullptr };

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

    if(cur->prev != nullptr)
        cur->prev->next = next;
    if (next->prev != nullptr)
        next->prev->next = cur;
    
    temp = cur->next;
    cur->next = next->next;
    next->next = temp;

    temp = cur->prev;
    cur->prev = next->prev;
    next->prev = temp;

    if(cur->next != nullptr)
        cur->next->prev = cur;
    if(next->next != nullptr)
        next->next->prev = next;
    
}

void deleteAll(doublyLinkedList *list, int val) //a)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");
    else if (list->count == 0)
        return;

    listNode *node{ list->first };

    while(node != nullptr)
    {
        listNode *next{ node->next };
        if (node->value == val)
            removeNode(list, node);

        node = next;
    }
}

void reverse(doublyLinkedList *list) //b)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");
    else if (list->count == 1 || list->count == 0)
        return;

    listNode *node{ list->first };
    listNode *newNext{ nullptr };

    while(node != nullptr)
    {
        listNode *next { node->next };
        node->prev = next;
        node->next = newNext;
        newNext = node;
        node = next;
    }

    node = list->first;
    list->first = list->last;
    list->last = node;
}

void sort(doublyLinkedList *list) //c)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");
    else if (list->count == 1 || list->count == 0)
        return;

    listNode *current{ list->first };
    
    for (int i{ 1 }; i < list->count; i++)
    {
        listNode *smallest{ current };
        listNode *node{ current->next };
        
        for (int j{ i }; j < list->count; j++)
        {
            if (smallest->value > node->value)
                smallest = node;

            node = node->next;
        }

        if (smallest != current)
        {
            swapNodes(list, current, smallest);
            current = smallest;
        }

        current = current->next;
    }  
}

void swapFirstLast(doublyLinkedList *list) //d)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");
    else if (list->count == 1 || list->count == 0)
        return;

    swapNodes(list, list->first, list->last);
}

void swapSecondPenultimate(doublyLinkedList *list) //e)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");

    switch(list->count)
    {
        case 2:
            swapFirstLast(list);
        case 0:
        case 1:
            return;
    } 

    listNode *second{ list->first->next };
    listNode *penultimate{ list->first };

    while(penultimate != nullptr && penultimate->next != list->last)
        penultimate = penultimate->next;

    swapNodes(list, second, penultimate);

}


/*int main()
{
    srand(time(NULL));
    int array[10];
    int length{ sizeof(array) / sizeof(int) };

    for (int i = 0; i < length; i++)
        array[i] = rand() % 2055; 

    doublyLinkedList *list{ convertArray(array, length) };

    std::cout << "List: " << list << '\n';
    deleteAll(list, 29);
    std::cout << list << '\n';
    
    reverse(list);
    std::cout << list << '\n';

    sort(list);
    std::cout << list << '\n';

    swapFirstLast(list);
    std::cout << list << '\n';

    swapSecondPenultimate(list);
    std::cout << list << '\n';

    doublyLinkedListDestroy(list);

    
    
    return 0;
} */