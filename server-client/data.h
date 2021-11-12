
#include "../sudoku/sudokuTable.h"

typedef struct data data_t;

data_t* data_new();

sudokuTable_t* data_getTable(data_t* data);

void data_setTable(data_t* data, sudokuTable_t* sudoku);

char* data_getMessage(data_t* data);

void data_setMessage(data_t* data, char* message);