// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#ifndef STACK_HXX
#define STACK_HXX

#include <cstddef>
#include "darray.hxx"

struct stack
{
    darray *array;
    size_t count;
};

stack *createStack();
void destroyStack(stack *st);
void destroyStackContent(stack *st);
void stackPush(stack *st, void *el);
bool isStackEmpty(stack *st);
void *stackPeek(stack *st);
void *stackPop(stack *st);

#endif