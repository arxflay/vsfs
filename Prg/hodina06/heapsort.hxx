// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#ifndef HEAPSORT_HXX
#define HEAPSORT_HXX

using compFunc = bool(*)(int a, int b);
bool asc(int a, int b);
bool desc(int a, int b);

int iLeft(int i);
int iRight(int i);
int iParent(int i);
void siftUp(int *arr, int i, compFunc comp);
void heapify(int *arr, int right, compFunc comp);
void reheap(int *arr, int right, compFunc comp);
void heapsort(int *arr, int right, compFunc comp);


#endif