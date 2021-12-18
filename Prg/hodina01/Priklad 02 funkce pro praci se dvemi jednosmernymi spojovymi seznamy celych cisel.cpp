// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>
#include <stdexcept>

#include "linkedlist.hxx"

int compare(linkedList *list1, linkedList *list2) //a)
{
    if (list1 == nullptr || list2 == nullptr)
        throw std::runtime_error("lists are null");
    else if (list1->count == list2->count)
        return 0;
    else if (list1->count == 0)
        return -1;
    else if (list2->count == 0)
        return 1;

    int smallestLength{ (list1->count < list2->count) ? list1->count : list2->count };
    
    listNode *list1Node{ list1->first };
    listNode *list2Node{ list2->first };

    for (int i{ 1 }; i < smallestLength; i++)
    {
        if (list1Node->value > list2Node->value)
            return 1;
        else if (list2Node->value > list1Node->value)
            return -1;
        
        list1Node = list1Node->next;
        list2Node = list2Node->next;
    }

    if(list1->count > list2->count)
        return 1;
    else if (list2->count > list1->count)
        return -1;
    
    return 0;
}

linkedList *copy(linkedList *list) //b)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");

    linkedList *newList{ linkedListCreate() };
    listNode *node{ list->first };

    while(node != nullptr)
    {
        push(newList, node->value);
        node = node->next;
    }

    return newList;
}

void split(linkedList *list, linkedList **evenList, linkedList **oddList) //c)
{
    if (list == nullptr)
        throw std::runtime_error("list is null");

    *evenList = linkedListCreate();
    *oddList = linkedListCreate();

    listNode *node{ list->first };
    for (int i{ 0 }; i < list->count; i++)
    {
        if (i % 2 == 0)
            push(*evenList, node->value);
        else
            push(*oddList, node->value);

        node = node->next;
    }
}

linkedList *merge(linkedList *list1, linkedList *list2) //d)
{
    if (list1 == nullptr || list2 == nullptr)
        throw std::runtime_error("lists are null");
    
    linkedList *list{ linkedListCreate() };

    listNode *list1Node{ list1->first };
    listNode *list2Node{ list2->first };

    int count{ 0 };

    while(list1Node != nullptr || list2Node != nullptr)
    {
        if ((count % 2 == 0 && list1Node != nullptr) || list2Node == nullptr)
        {
            push(list, list1Node->value);
            list1Node = list1Node->next;
        }
        else if ((count % 2 == 1 && list2Node != nullptr) || list1Node == nullptr)
        {
            push(list, list2Node->value);
            list2Node = list2Node->next;
        }
        count++;
    }

    return list;
}

int main()
{
    int a1[]{ 15, 6, 19, 25, 7, 0, 6, 1, 85 };
    int a2[]{ 15, 6, 8, 66, 2, 3 };
    int lengthA1{ sizeof(a1) / sizeof(int) };
    int lengthA2{ sizeof(a2) / sizeof(int) };
    linkedList *list1{ convertArray(a1, lengthA1) };
    linkedList *list2{ convertArray(a2, lengthA2) };

    std::cout << compare(list1, list2) << '\n';

    linkedList *list1Copy{ copy(list1) };
    std::cout << "list copy: " << list1Copy << '\n';

    linkedList *evenList{ nullptr };
    linkedList *oddList{ nullptr };
    split(list1, &evenList, &oddList);
    std::cout << "evenList: " << evenList << '\n';
    std::cout << "oddList: " << oddList << '\n';

    linkedList *mergedList{ merge(evenList, oddList) };
    std::cout << "mergedList: " << mergedList << '\n';

    linkedListDestroy(list1);
    linkedListDestroy(list2);
    linkedListDestroy(list1Copy);
    linkedListDestroy(evenList);
    linkedListDestroy(oddList);
    linkedListDestroy(mergedList);
    return 0;
}