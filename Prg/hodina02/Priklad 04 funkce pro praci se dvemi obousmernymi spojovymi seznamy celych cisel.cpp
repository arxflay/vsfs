// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>
#include "doublylinkedlist.hxx"

void split(doublyLinkedList **l1, doublyLinkedList **l2, doublyLinkedList *main)
{
    if (main == nullptr)
        throw std::runtime_error("main list is null");
    else if (main->count == 0)
        return;

    *l1 = doublyLinkedListCreate();
    *l2 = doublyLinkedListCreate();
    listNode *node{ main->first };

    for (int i{ 0 }; i < main->count; i++)
    {
        if (i % 2 == 0)
            push(*l1, node->value);
        else
            push(*l2, node->value);

        node = node->next;
    }
}

doublyLinkedList *merge(doublyLinkedList *l1, doublyLinkedList *l2)
{
    if (l1 == nullptr || l2 == nullptr)
        throw std::runtime_error("lists are null");
    
    doublyLinkedList *list{ doublyLinkedListCreate() };

    listNode *list1Node{ l1->first };
    listNode *list2Node{ l2->first };

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
    int array[]{ 15, 6, 8, 66, 2 };
    int length{ sizeof(array) / sizeof(int) };
    doublyLinkedList *list{ convertArray(array, length) };
    doublyLinkedList *l1{ nullptr }, *l2{ nullptr };
    
    split(&l1, &l2, list);
    std::cout << l1 << '\n';
    std::cout << l2 << '\n';

    doublyLinkedList *l3{ merge(l1, l2) };
    std::cout << l3 << '\n';

    doublyLinkedListDestroy(list);
    doublyLinkedListDestroy(l1);
    doublyLinkedListDestroy(l2);
    doublyLinkedListDestroy(l3);

    return 0;
}