// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "heapsort.hxx"

using compFunc = bool(*)(int a, int b);

bool asc(int a, int b)
{
    return a > b;
}

bool desc(int a, int b)
{
    return a < b;
}

void writeArray(int *array, int length)
{
    for (int i{ 0 }; i < length; i++)
        std::cout << array[i] << ' ';
        
    std::cout << '\n';
}

int iLeft(int i) { return 2 * i + 1; }
int iRight(int i) { return 2 * i + 2; }
int iParent(int i) { return ((i - 1) / 2); }

void siftUp(int *arr, int i, compFunc comp)
{
    int parent{ iParent(i) };
    int cur = i;

    while(parent >= 0)
    {
        if (comp(arr[cur], arr[parent]))
        {
            std::swap(arr[cur], arr[parent]);
            cur = parent;
            parent = iParent(cur);
        }
        else
            break;
    }
}

void heapify(int *arr, int right, compFunc comp)
{
    int elements{ right - 1 };

    while (elements >= 0)
    {
        siftUp(arr, right - elements, comp);
        elements--;
    }
}

void reheap(int *arr, int right, compFunc comp)
{
    int index{ 0 };
    int l{ iLeft(index) };
    int r{ iRight(index) };

    while(l <= right)
    {
        if (r <= right && comp(arr[r], arr[index]) && comp(arr[r], arr[l]))
        {
            std::swap(arr[index], arr[r]);
            index = r;
        }
        else if (comp(arr[l], arr[index]))
        {
            std::swap(arr[index], arr[l]);
            index = l;
        }
        else
            break;

        l = iLeft(index);
        r = iRight(index);
    }
}

void heapsort(int *arr, int right, compFunc comp)
{
    if (right <= 0)
        return;

    heapify(arr, right, comp);
    int last{ right };

    while(last != 0)
    {
        std::swap(arr[0], arr[last--]);
        reheap(arr, last, comp);
    }
}