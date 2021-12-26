// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>
#include "binarytree.hxx"

int mid(int length)
{
    return length / 2;
}

void selectionSort(int *array, int length)
{
    for (int i{ 0 }; i < length - 1; i++)
    {
        int smallestIndex = i;
        for (int j{ i + 1 }; j < length; j++)
        {
            if (array[smallestIndex] > array[j])
                smallestIndex = j;
        }

        if (smallestIndex != i)
        {
            int temp{ array[i] };
            array[i] = array[smallestIndex];
            array[smallestIndex] = temp;
        }
    }
}

void createBalancedTree(treeNode *node, int *array, int left, int right)
{
    if (node == nullptr)
        return;
        
    int midArr{ mid(left + right) };

    if(left < midArr)
    {
        insert(node, array[mid(left + midArr)]);
        createBalancedTree(node->left,  array, left, midArr);
    }

    if(midArr < right)
    {
        insert(node, array[mid(midArr + right)]);
        createBalancedTree(node->right, array, midArr + 1, right);
    }
}

treeNode *arrayToBalancedTree(int *array, int length)
{
    int *copyArray { new int[length] };
    std::copy(array, array + length, copyArray);
    selectionSort(copyArray, length);

    treeNode *root{ insert(nullptr, copyArray[mid(length)]) };
    createBalancedTree(root, copyArray, 0, length);

    delete[] copyArray;

    return root;
}

static inline void write_cb(treeNode *node)
{
    std::cout << node->value << ' ';
}

int main()
{
    int array[7]{ 5, 5, 3, 2, 7, 8, 10 };
    treeNode *root{ arrayToBalancedTree(array, 7) };
    traverse(root, write_cb);
    traverse(root, destroy_cb);
}
