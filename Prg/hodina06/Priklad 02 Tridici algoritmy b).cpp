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

void writeArray(int *array, int length)
{
    for (int i{ 0 }; i < length; i++)
        std::cout << array[i] << ' ';
        
    std::cout << '\n';
}

int iLeft(int i) { return 2 * i + 1; }
int iRight(int i) { return 2 * i + 2; }
int iParent(int i) { return ((i - 1) / 2); }

void swap(int &a, int &b)
{
    int temp{ a };
    a = b;
    b = temp;
}

void siftUp(int *arr, int i)
{
    int parent{ iParent(i) };
    int cur = i;

    while(parent >= 0)
    {
        if (arr[cur] < arr[parent])
        {
            swap(arr[cur], arr[parent]);
            cur = parent;
            parent = iParent(cur);
        }
        else
            break;
    }
}

void heapify(int *arr, int right)
{
    int elements{ right - 1 };

    while (elements >= 0)
    {
        siftUp(arr, right - elements);
        elements--;
    }
}

void reheap(int *arr, int right)
{
    int index{ 0 };
    int l{ iLeft(index) };
    int r{ iRight(index) };

    while(l <= right)
    {
        if (r <= right && arr[r] < arr[index] && arr[r] < arr[l])
        {
            swap(arr[index], arr[r]);
            index = r;
        }
        else if (arr[l] < arr[index])
        {
            swap(arr[index], arr[l]);
            index = l;
        }
        else
            break;

        l = iLeft(index);
        r = iRight(index);
    }
}

void heapsort(int *arr, int right)
{
    if (right <= 0)
        return;

    heapify(arr, right);
    int last{ right };

    while(last != 0)
    {
        swap(arr[0], arr[last--]);
        reheap(arr, last);
    }  
}

int main()
{
    srand(time(NULL));
    int array[15]{};
    constexpr int length{ sizeof(array) / sizeof(int) };

    for (int i{ 0 }; i < length; i++)
        array[i] = rand() % 2555;
    
    std::cout << "original array:   ";
    writeArray(array, length);

    heapsort(array, length - 1);
    std::cout << "heapsorted array: ";
    writeArray(array, length);

    return 0;
}