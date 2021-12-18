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

linkedList *convertString(const std::string& text)
{
    linkedList *list{ linkedListCreate() };
    for (int i{ static_cast<int>(text.length() - 1) }; i >= 0; i--)
    {
        char val { static_cast<char>(text[i] - '0') };
        if (val >= 0 && val <= 9)
            push(list, static_cast<int>(val));
    }

    return list;
}

linkedList *sum(linkedList *list1, linkedList *list2)
{
    int shift{ 0 };
    int sum{ 0 };
    linkedList *list{ linkedListCreate() };
    listNode *list1Node{ list1->first };
    listNode *list2Node{ list2->first };

    while (shift != 0 || list1Node != nullptr || list2Node != nullptr)
    {
        if (list1Node != nullptr && list2Node != nullptr)
        {
            sum = list1Node->value + list2Node->value + shift ;
            list1Node = list1Node->next;
            list2Node = list2Node->next;
        }
        else if (list1Node != nullptr)
        {
            sum = list1Node->value + shift;
            list1Node = list1Node->next;
        }
        else if (list2Node != nullptr)
        {
            sum = list2Node->value + shift;
            list2Node = list2Node->next;
        }
        else if (shift != 0)
            sum = shift;

        push(list, sum % 10);
        shift = sum / 10;
    }

    return list;
}

std::string toString(linkedList *number)
{
    std::string text{};
    listNode *node{ number->first };

    while (node != nullptr)
    {
        text = static_cast<char>(node->value + '0') + text;
        node = node->next;
    }

    return text;
}

int main()
{
    std::string n1{ "1762569" };
    std::string n2{ "9500954" };
    linkedList *l1{ convertString(n1) };
    linkedList *l2{ convertString(n2) };
    linkedList *l3{ sum(l1, l2) };
    std::string n3{ toString(l3) };

    std::cout << "l1: " << l1 << '\n' 
        << "l2: " << l2 << '\n'
        << "l1 + l2: " << l3 << '\n'
        << "toString sum: " << n3 << '\n';

    return 0;
}