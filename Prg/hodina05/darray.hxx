// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#ifndef DARRAY_HXX
#define DARRAY_HXX

#include <cstddef>

struct darray
{
    void **data;
    size_t length;
};

darray *createDarray(size_t initialLength);
void destroyDarray(darray *arr);
void expand(darray *arr);

#endif