// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "stack.hxx"

void pushIntCopy(stack *st, int el)
{
    int *copy{ new int{ el }};
    stackPush(st, copy);
}

void writeArray(int *array, int length)
{
    for (int i{ 0 }; i < length; i++)
        std::cout << array[i] << ' ';
        
    std::cout << '\n';
}

void swap(int &a, int &b)
{
    int temp{ a };
    a = b;
    b = temp;
}

int pivot(int *array, int left, int right) //a)
{
    int p{ left };

    for (int i{ left }; i < right; i++)
        if (array[i] > array[right])
            swap(array[i], array[p++]);

    swap(array[p], array[right]);

    return p;
}

void quickSortRec(int *array, int left, int right) //a)
{
    if (left < right)
    {
        int p{ pivot(array, left, right) };
        quickSortRec(array, left, p - 1);
        quickSortRec(array, p + 1, right);
    }
}


void merge(int *array, int left, int mid, int right) //b)
{
    int *aux{ new int[(right + 1) - left]{} };
    int i{ 0 }, l{ left }, r{ mid + 1 };

    for (; l <= mid && r <= right; i++)
    {
        if (array[l] > array[r])
            aux[i] = array[l++];
        else
            aux[i] = array[r++];
    }

    while (l <= mid)
        aux[i++] = array[l++];
    while (r <= right)
        aux[i++] = array[r++];

    for (i = left; i <= right; i++)
        array[i] = aux[i - left];
    
    delete[] aux;
}

void mergeSortRec(int *array, int left, int right) //b)
{
    if (left < right)
    {
        int mid{ (left + right) / 2 };
        mergeSortRec(array, left, mid);
        mergeSortRec(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void quickSort(int *array, int right) //c)
{
    stack *st{ createStack() };

    int l{ 0 };
    int r{ right };

    while(true)
    {
        if (l < r)
        {
            int p{ pivot(array, l, r) };
            pushIntCopy(st, r);
            pushIntCopy(st, p + 1);
            pushIntCopy(st, p - 1);
            pushIntCopy(st, l);
        }

        if (isStackEmpty(st))
            break;

        int *lptr{ (int*)stackPop(st) };
        int *rptr{ (int*)stackPop(st) };
        l = *lptr;
        r = *rptr;

        delete lptr;
        delete rptr;
        
    }

    destroyStack(st);
}

void mergeSort(int *array, int right) //d)
{
    int subLen{ 2 };
    bool exit{ false };

    while (!exit)
    {
        if (subLen >= right)
        {
            subLen = right;
            exit = true;
        }

        int i{ 0 };
        int curSubLen{ 0 };

        while (i < right)
        {
            curSubLen = (i + subLen) >= right ? right - i : subLen - 1;

            int l{ i };
            int r{ i + (curSubLen) };
            int mid{ (r + l) / 2 };

            merge(array, l, mid, r);

            i += subLen ;
        }

        if (!exit)
            subLen *= 2;
    }
}

int main()
{
    srand(time(NULL));
    int array[15]{};
    int copy[15]{};
    constexpr int length{ sizeof(array) / sizeof(int) };
    static_assert(sizeof(copy) && sizeof(array));

    for (int i{ 0 }; i < length; i++)
        array[i] = rand() % 2555;
    std::copy(array, array + length, copy);
    
    std::cout << "original array:       ";
    writeArray(array, length);

    quickSortRec(array, 0, length - 1);
    std::cout << "quickSortedRec array: ";
    writeArray(array, length);

    std::copy(copy, copy + length, array);

    mergeSortRec(array, 0, length - 1);
    std::cout << "mergesortedRec array: ";
    writeArray(array, length);

    std::copy(copy, copy + length, array);

    quickSort(array, length - 1);
    std::cout << "quicksorted array:    ";
    writeArray(array, length);

    std::copy(copy, copy + length, array);

    mergeSort(array, length - 1);
    std::cout << "mergesorted array:    ";
    writeArray(array, length);
}