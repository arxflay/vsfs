// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <ctime>

#include "linkedlist.hxx"

linkedList *linkedListCreate()
{
    linkedList *list{ new linkedList{} };
    list->first = nullptr;
    list->last = nullptr;
    list->count = 0;

    return list;
}

void pushNode(linkedList *list, listNode *node)
{
    if (list->first == nullptr)
    {
        list->first = node;
        list->last = node;
    }
    else
    {
        list->last->next = node;
        list->last = node;
    }

    list->count++;
}

void push(linkedList *list, int value)
{
    listNode *node{ new listNode{} };
    node->next = nullptr;
    node->value = value;

    pushNode(list, node);
}

int shift(linkedList *list)
{
    if (list->first == nullptr)
        throw std::runtime_error("list is empty");

    int value = list->first->value;

    if (list->first->next == nullptr)
    {
        delete list->first;
        list->first = nullptr;
        list->last = nullptr;
    }
    else
    {
        listNode *newFirst{ list->first->next };
        delete list->first;
        list->first = newFirst;
    }

    list->count--;

    return value;
}

linkedList *convertArray(int *array, int length)
{
    linkedList *list{ linkedListCreate() };
    for (int i{ 0 }; i < length; i++)
        push(list, array[i]);

    return list;
}

void linkedListDestroy(linkedList *list)
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

std::ostream& operator<< (std::ostream& out, linkedList *list) //only for testing
{
    listNode *node{ list->first };
    while(node != nullptr)
    {
        out << node->value << ' ';
        node = node->next;
    }

    return out;
}

void removeNode(linkedList *list, listNode *node, listNode *prev)
{
    if (node == list->first)
        shift(list);
    else
    {
        if(node->next == nullptr)
            list->last = prev;

        prev->next = node->next;
        list->count--;

        delete node;

    }
}

void swapNodes(linkedList *list, listNode *cur, listNode *prev, listNode *next, listNode *nextPrev)
{
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

    if (prev != nullptr)
        prev->next = next;
    if (nextPrev != nullptr)
        nextPrev->next = cur;

    listNode *temp{ cur->next };

    cur->next = next->next;
    next->next = temp;
   
}

void saveList(linkedList *list, const std::string& filename) //a)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");

    std::ofstream out{};
    out.exceptions(out.failbit | out.badbit);
    out.open(filename, std::ofstream::binary | std::ofstream::out);

    listNode *node{ list->first };
    
    while(node != nullptr)
    {
        listNode *next{ node->next };
        out.write((const char*)node, sizeof(listNode));
        node = next;
    }

    out.close();
}

linkedList *loadList(const std::string& filename) //b)
{
    std::ifstream in{};
    in.exceptions(in.failbit | in.badbit);
    in.open(filename, std::ifstream::binary | std::ifstream::in);
    in.seekg(0, in.end);
    std::streamoff end{ in.tellg() };

    in.seekg(0, in.beg);

    long count{ static_cast<long>(end / sizeof(listNode)) };

    linkedList *list{ linkedListCreate() };

    for (long i{ 0 }; i < count; i++)
    {
        listNode *node{ new listNode() };
        in.readsome((char*)node, sizeof(listNode));
        pushNode(list, node);
    }

    in.close();

    return list;
}

int countOccurences(linkedList *list, int val) //c)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");

    int count{ 0 };
    listNode *node{ list->first };

    while(node != nullptr)
    {
        listNode *next{ node->next };
        if (node->value == val)
            count++;
        node = next;
    }

    return count;
}

void removeLastMatch(linkedList *list, int val) //d)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");
    else if (list->count == 0)
        return;

    listNode *node{ list->first };
    listNode *prev{ nullptr };
    listNode *prevMatch{ nullptr };
    listNode *match{ nullptr };

    while(node != nullptr)
    {
        listNode *next{ node->next };

        if (node->value == val)
        {
            match = node;
            prevMatch = prev;
        }

        prev = node;
        node = next;
    }

    if (match != nullptr)
        removeNode(list, match, prevMatch);
}

void removeHeighiest(linkedList *list) //e)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");
    else if (list->count == 0)
        return;

    listNode *node{ list->first };
    listNode *prev{ nullptr };
    listNode *prevHeighiest{ nullptr };
    listNode *heighiest{ node };

    while(node != nullptr)
    {
        listNode *next{ node->next };

        if (node->value > heighiest->value)
        {
            prevHeighiest = prev;
            heighiest = node;
        }

        prev = node;
        node = next;
    }
    
    if (heighiest != nullptr)
        removeNode(list, heighiest, prevHeighiest);

}

void reverse(linkedList *list) //f)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");
    else if (list->count <= 1)
        return;

    listNode *node{ list->first };
    listNode *newNext{ nullptr };

    while(node != nullptr)
    {
        listNode *next{ node->next };
        node->next = newNext;
        newNext = node;
        node = next;
    }
    
    node = list->first;
    list->first = list->last;
    list->last = node;
}

void sort(linkedList *list) //g)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");
    else if (list->count <= 1)
        return;

    listNode *current{ list->first };
    listNode *prev{ nullptr };

    for (int i{ 1 }; i < list->count ; i++)
    {
        listNode *biggest{ current };
        listNode *biggestPrev{ prev };
        listNode *node{ current->next };
        listNode *tempPrev{ current };
        for (int j{ i }; j < list->count; j++)
        {
            if (biggest->value < node->value)
            {
                biggest = node;
                biggestPrev = tempPrev;
            }

            tempPrev = node;
            node = node->next;
        }

        if (biggest != current)
        {
            swapNodes(list, current, prev, biggest, biggestPrev);
            current = biggest;
        }

        prev = current;
        current = current->next;
    }
}

void swapFirstLast(linkedList *list) //h)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");
    else if (list->count <= 1)
        return;

    listNode *prev{ list->first };

    while(prev != nullptr && prev->next != list->last)
        prev = prev->next;

    swapNodes(list, list->first, nullptr, list->last, prev);

}

void swapSecondPenultimate(linkedList *list) //i)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");

    switch(list->count)
    {
        case 2:
            swapNodes(list, list->first, nullptr, list->last, list->first);
        case 0:
        case 1:
            return;
    }

    listNode *second{ list->first->next };
    listNode *secondPrev{ list->first };
    listNode *penultimatePrev{ nullptr };
    listNode *penultimate{ list->first };

    while(penultimate != nullptr && penultimate->next != list->last)
    {
        penultimatePrev = penultimate;
        penultimate = penultimate->next;
    }

    swapNodes(list, second, secondPrev, penultimate, penultimatePrev);
}

int main()
{
    srand(time(NULL));
    int array[10]{};
    int length{ sizeof(array) / sizeof(int) };

    for (int i = 0; i < length; i++)
        array[i] = rand() % 2055;

    linkedList *list{ convertArray(array, length) };
    std::cout << "List: " << list << '\n';
    saveList(list, "spojak.txt");
    linkedListDestroy(list);

    list = loadList("spojak.txt");
    std::cout << "New list: " << list << '\n';

    std::cout << "Count 29: " << countOccurences(list, 29) << '\n';
    removeLastMatch(list, 8);
    std::cout << "after removeLastMatch List: " << list << '\n' ;
    removeHeighiest(list);
    std::cout << "after removeHeighiest List: " << list << '\n';
    reverse(list); 
    std::cout << "after reverse List: " << list << '\n';
    sort(list);
    std::cout << "after sorting List: " << list << '\n';  
    swapFirstLast(list);
    std::cout << "after swapFirstLast List: " << list << '\n';
    swapSecondPenultimate(list);
    std::cout << "after swapSecondPenultimate List: " << list << '\n' ;

    linkedListDestroy(list);

    return 0;
}


