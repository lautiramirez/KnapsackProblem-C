#include <stdio.h>
#include <stdlib.h>

#include "sort.h"

void swap(item_t *a, bool *selected, unsigned int x, unsigned int y) { 
    item_t temp = a[x]; 
    bool bool_tmp = selected[x];
    a[x] = a[y]; 
    selected[x] = selected[y];
    a[y] = temp;
    selected[y] = bool_tmp; 
}

unsigned int partition(item_t *a, bool *selected, unsigned int izq, unsigned int der){       
    
    unsigned int ppiv = izq;
    unsigned int i, j;
    i = izq + 1;
    j = der;

    while (i <= j){

        if (item_value(a[i]) > item_value(a[ppiv])){
            i++;
        }

        else if (item_value(a[ppiv]) > item_value(a[j])){
            j--;
        }

        else{
            swap(a,selected, i,j);
            i++;
            j--;
        }
        
    }

    swap(a, selected, ppiv, j);
    ppiv = j;
    
    return ppiv;
}

void quick_sort_rec(item_t *a, bool *selected, unsigned int izq, unsigned int der){

    unsigned int ppiv = 0;
    if (izq < der){
        ppiv = partition(a, selected, izq,der);
        if (ppiv == 0){
            quick_sort_rec(a,selected, izq,ppiv);
        }
        else{
            quick_sort_rec(a, selected, izq,ppiv-1);
        }
        quick_sort_rec(a,selected, ppiv+1,der);          
    }  
}

void quick_sort(item_t *a, bool *selected, unsigned int length){
    quick_sort_rec(a, selected, 0,(length == 0) ? 0 : length - 1);
}