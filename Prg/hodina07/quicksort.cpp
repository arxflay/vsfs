// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <functional>
#include "quicksort.hxx"

static inline int pivot(int *array, int left, int right)
{
    int p{ left };

    for (int i{ left }; i < right; i++)
        if (array[i] < array[right])
            std::swap(array[i], array[p++]);

    std::swap(array[p], array[right]);

    return p;
}

void quicksortRec(int *array, int left, int right)
{
    if (left < right)
    {
        int p{ pivot(array, left, right) };
        quicksortRec(array, left, p - 1);
        quicksortRec(array, p + 1, right);
    }
}

void quicksort(int *array, int right)
{
    if (right == 0)
        return;
    
    quicksortRec(array, 0, right);
}