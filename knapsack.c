#include <stdio.h>
#include <stdlib.h>

#include "knapsack.h"

/* Creamos una funcion auxilar que nos devuelve el maximo de dos valores */
value_t max_value(value_t a, value_t b){
    value_t maximo_valor = (a > b)? a : b;
    return maximo_valor;
}

value_t knapsack_backtracking(item_t* items, unsigned int array_length, weight_t max_weight){   
    
    value_t res_final = 0;   
    
    /* Caso base */
    if(array_length == 0 || max_weight == 0){ 
        res_final = 0;
    }

    else{

        /* Comenzamos del ultimo elemento del array */
        item_t item_actual = items[array_length-1];
        weight_t peso_actual = item_weight(item_actual);
        value_t valor_actual = item_value(item_actual);

        if(peso_actual > max_weight){     
            res_final = knapsack_backtracking(items, array_length-1, max_weight);
        }
        else{
            /* Tenemos dos casos: Esta o no esta el elemento incluido */
            value_t no_lo_sumo = knapsack_backtracking(items, array_length-1, max_weight);
            value_t lo_sumo =  valor_actual + knapsack_backtracking(items, array_length-1, max_weight - peso_actual);

            res_final = max_value(no_lo_sumo, lo_sumo);
        }
    }
    return res_final;
}

value_t knapsack_dynamic(item_t* items, unsigned array_length, weight_t max_weight){

    /* Creamos un tablero con un array bidimensional dinamico */
    value_t **tabla = calloc(array_length + 1, sizeof(value_t*));
    for (unsigned int j = 0; j < array_length + 1; j++){
        tabla[j] = calloc(max_weight + 1, sizeof(value_t));
    }

    /* Inicializamos la comumna 0 y la fila 0 con el valor cero */
    for(unsigned int j = 1; j <= max_weight; j++){
        tabla[0][j] = 0;
    }
    for(unsigned int i = 0; i <= array_length; i++){
        tabla[i][0] = 0;
    }

    /* Rellenamos el tablero con los valores correspondientes */
    for (unsigned int i = 1; i <= array_length; i++){
        for (unsigned int j = 1; j <= max_weight; j++){
            
            weight_t peso_item = item_weight(items[i-1]);
            value_t valor_item = item_value(items[i-1]);

            /* Caso: Cuando el peso del item no entra en la mochila */
            if(peso_item > j){
                tabla[i][j] = tabla[i-1][j];
            }

            else{

                /* Tenemos dos opciones: Guardar el item, o no guardarlo */
                value_t suma_valor = valor_item + tabla[i-1][j - peso_item];
                value_t no_suma_valor = tabla[i-1][j];

                /* Rellenamos con el valor optimo */
                tabla[i][j] = max_value(no_suma_valor, suma_valor);
        
            }
        }
    }    

    /* Guardamos el valor optimo en una variable */
    value_t res_final = tabla[array_length][max_weight];

    /* Liberamos la memoria que pedimos para crear el tablero */
    for (unsigned int j = 0; j < array_length + 1; j++){
        free(tabla[j]);
        tabla[j] = NULL;
    }
    free(tabla);
    tabla = NULL;

    return res_final;
}


value_t knapsack_dynamic_selection(item_t* items, bool* selected, unsigned int array_length, weight_t max_weight){
     
    value_t **tabla = calloc(array_length + 1, sizeof(value_t*));
    for (unsigned int j = 0; j < array_length + 1; j++){
        tabla[j] = calloc(max_weight + 1, sizeof(value_t));
    }

    for(unsigned int j = 1; j <= max_weight; j++){
        tabla[0][j] = 0;
    }
    for(unsigned int i = 0; i <= array_length; i++){
        tabla[i][0] = 0;
    }

    for (unsigned int i = 1; i <= array_length; i++){
        for (unsigned int j = 1; j <= max_weight; j++){

            weight_t peso_item = item_weight(items[i-1]);
            value_t valor_item = item_value(items[i-1]);
            
            if(peso_item > j){
                tabla[i][j] = tabla[i-1][j];
            }

            else{

                value_t suma_valor = valor_item + tabla[i-1][j - peso_item];
                value_t no_suma_valor = tabla[i-1][j];

                tabla[i][j] = max_value(no_suma_valor, suma_valor);
            
            }
        }
    }

    value_t res_final = tabla[array_length][max_weight];

    /* Para seleccionar los items utilizó el Algortimo de Floyd */
    unsigned int r = array_length;
    weight_t s = max_weight;

    while (tabla[r][s] > 0){
        if(tabla[r][s] == tabla[r-1][s]){
            selected[r-1] = false;
        }
        else{
            selected[r-1] = true;
            s = s - item_weight(items[r-1]);
        }
        r--;
    }
    
    for (unsigned int j = 0; j < array_length + 1; j++){
        free(tabla[j]);
        tabla[j] = NULL;
    }
    free(tabla);
    tabla = NULL;

    return res_final;
}
