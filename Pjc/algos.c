#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "algos.h"

static inline int pivot(int *array, int left, int right)
{
    int p = left;

    for (int i = left ; i < right; i++)
        if (array[i] > array[right])
        {
            swap(array[i], array[p], int);
            p++;
        }
    
    swap(array[p], array[right], int);

    return p;
}

void quicksort(int *array, int left, int right)
{
    if (left < right)
    {
        int p = pivot(array, left, right);
        quicksort(array, left, p - 1);
        quicksort(array, p + 1, right);
    }
}

static inline void merge(int *array, int left, int mid, int right)
{
    int *aux = (int*)calloc((right + 1) - left, sizeof(int));
    int i = 0, l = left, r = mid + 1;

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
    
    free(aux);
}

void mergesort(int *array, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergesort(array, left, mid);
        mergesort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

int better_random(int min, int max)
{
    static double fraction = 1.0 / (RAND_MAX + 1.0);
    return min + ((max - min + 1.0) * fraction * rand());
}

bool fEqual(float a, float b)
{ 
    return (fmax(fabs(a), fabs(b)) - fmin(fabs(a), fabs(b))) <= __FLT_EPSILON__; 
}

bool dEqual(double a, double b)
{ 
    return (fmax(fabs(a), fabs(b)) - fmin(fabs(a), fabs(b))) <= __DBL_EPSILON__;
}

int main()
{
}