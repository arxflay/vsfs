// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>

struct ringDoublyList
{
    ringDoublyList *next;
    ringDoublyList *prev;
    int value;
};

ringDoublyList *linkedlistCreate(int val)
{
    ringDoublyList *list{ new ringDoublyList{} };
    list->next = list;
    list->prev = list;
    list->value = val;

    return list;
}

void linkedlistDestroy(ringDoublyList *list)
{
    if (list == nullptr)
        return;

    ringDoublyList *first{ list };
    bool firstPassed{ false };

    while(list != first || !firstPassed )
    {
        if (list == first)
            firstPassed = true;

        ringDoublyList *next{ list->next };
        delete list;
        list = next;
    }
} 

void write(ringDoublyList *list) //a)
{
    if (list == nullptr)
        return;

    ringDoublyList *first{ list };
    bool firstPassed{ false };

    while(list != first || !firstPassed)
    {
        if (list == first)
            firstPassed = true;

        std::cout << list->value << ' ';
        list = list->next;
    }

    std::cout << '\n';
}

ringDoublyList *find(ringDoublyList *list, int val) //b)
{
    ringDoublyList *first{ list };
    bool firstPassed{ false };

    while(list != first || !firstPassed)
    {
        if (list == first)
            firstPassed = true;

        if (list->value == val)
            return list;
        
        list = list->next;
    }

    return nullptr;
}

ringDoublyList *insertAfter(ringDoublyList *list, int val) //c)
{
    ringDoublyList *node{ linkedlistCreate(val) };
 
    if (list == nullptr)
        return node;
    else if (list->next == list)
        node->next = list;
    else
    {
        node->next = list->next;
        list->next->prev = node;
    }

    list->next = node;
    node->prev = list;

    return list;
}

ringDoublyList *deleteList(ringDoublyList *list) //d)
{
    if (list == nullptr)
        return nullptr;

    ringDoublyList *newStart{ nullptr };

    if (list->next != list)
    {
        list->prev->next = list->next;
        list->next->prev = list->prev;
        newStart = list->next;
    }
    else
        newStart = nullptr;
        
    delete list;

    return newStart;
}

int main()
{
    ringDoublyList *list { nullptr };

    list = insertAfter(list, 5);
    write(list);
    list = insertAfter(list, 7);
    write(list);
    list = insertAfter(list, 2);
    write(list);

    insertAfter(list->next, 1);
    write(list);

    list = insertAfter(list->next, 9);
    write(list);

    deleteList(list->next);
    write(list);

    list = find(list, 7);
    list = deleteList(list);
    write(list);

    linkedlistDestroy(list);
    return 0;
}
