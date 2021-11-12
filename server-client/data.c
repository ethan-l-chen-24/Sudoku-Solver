
#include <stdio.h>
#include <stdlib.h>
#include "../sudoku/sudokuTable.h"


typedef struct data {
    char* message;
    sudokuTable_t* table;
} data_t;

data_t* data_new() {
    data_t* data = malloc(sizeof(data_t));
    return data;
}

sudokuTable_t* data_getTable(data_t* data) {
    if(data == NULL) return NULL;
    return data->table;
}

void data_setTable(data_t* data, sudokuTable_t* sudoku) {
    data->table = sudoku;
}

char* data_getMessage(data_t* data) {
    if(data == NULL) return NULL;
    return data->message;
}

void data_setMessage(data_t* data, char* message) {
    data->message = message;
}