// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <cassert>
#include <cstdlib>
#include "darray.hxx"

darray *createDarray(size_t initialLength)
{
    assert(initialLength != 0 && "ERROR: initialLength equals to 0");

    darray *array{ new darray{} };
    array->length = initialLength;
    array->data = (void**)calloc(initialLength, sizeof(void*));
    
    for (size_t i{ 0 }; i < array->length; i++)
        array->data[i] = nullptr;
    
    return array;
}

void destroyDarray(darray *arr)
{
    if (arr)
    {
        if (arr->data)
            free(arr->data);

        delete arr;
    }
}

void expand(darray *array)
{
    size_t oldLength{ array->length };
    array->length *= 2;
    array->data = (void**)realloc(array->data, array->length * sizeof(void*));
    
    for (size_t i{ oldLength }; i < array->length; i++)
        array->data[i] = nullptr;
}

