// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <cstdlib>
#include <cstring>
#include <cassert>
#include "stack.hxx"

stack *createStack()
{
    stack *s{ new stack };
    s->array = createDarray(2);
    s->count = 0;

    return s;
}

void destroyStackContent(stack *st)
{
    for (size_t i{ 0 }; i < st->count; i++)
        free(st->array->data[i]);
}

void destroyStack(stack *st)
{
    destroyDarray(st->array);
    delete st;
}

void stackPush(stack *st, void *el)
{
    if (st->count == st->array->length)
        expand(st->array);

    st->array->data[st->count++] = el;
}

bool isStackEmpty(stack *st)
{
    return st->count == 0;
}

void *stackPeek(stack *st)
{
    if (st->count == 0)
        return nullptr;

    return st->array->data[st->count - 1];
}


void *stackPop(stack *st)
{
    if (st->count == 0)
        return nullptr;

    return st->array->data[--st->count];
}