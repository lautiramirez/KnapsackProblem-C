#ifndef SORT_H
#define SORT_H

#include <stdbool.h>
#include "knapsack.h"

void swap(item_t *a, bool *selected, unsigned int x, unsigned int y);

unsigned int partition(item_t *a, bool *selected, unsigned int izq, unsigned int der);  

void quick_sort_rec(item_t *a, bool *selected, unsigned int izq, unsigned int der);

void quick_sort(item_t *a, bool *selected, unsigned int length);

#endif
