#ifndef ALGOS_H
#define ALGOS_H

#include <stdbool.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define swap(a, b, type) type temp = (a);\
                          (a) = (b);\
                          (b) = temp

#endif