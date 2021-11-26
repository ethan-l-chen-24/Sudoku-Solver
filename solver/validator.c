/*
 * validator.c - holds three boolean matrices to check if a number already exists
 *               in a row, column, or box 
 *
 * Ethan Chen, Jeffrey Jiang, Bansharee Ireen
 * 
 * Nov 13, 2021
 * CS50, Fall 2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct validator {
    bool** row;
    bool** col;
    bool*** boxes;
    int dimension;
}
validator_t;

// struct methods

/*********** validator_new **************/
/*
 * see validator.h for more information
 */
validator_t* validator_new(int dimension) {

    // create memory for the struct itself
    validator_t* val = malloc(sizeof(validator_t));
    if (val == NULL) return NULL;

    // allocate memory for the row matrix
    bool** row = calloc(dimension, sizeof(bool * ));
    for (int i = 0; i < dimension; i++) {
        row[i] = (bool * ) calloc(dimension + 1, sizeof(bool));
    }

    // allocate memory for the col matrix
    bool** col = calloc(dimension, sizeof(bool * ));
    for (int i = 0; i < dimension; i++) {
        col[i] = (bool * ) calloc(dimension + 1, sizeof(bool));
    }

    int sqrtDimension = (int) sqrt(dimension);

    // allocate memory for the boxes matrix
    bool*** boxes = calloc(sqrtDimension, sizeof(bool ** ));
    for (int i = 0; i < sqrtDimension; i++) {
        boxes[i] = (bool**) calloc(sqrtDimension, sizeof(bool * ));
        for (int j = 0; j < sqrtDimension; j++) {
            boxes[i][j] = (bool*) calloc(dimension + 1, sizeof(bool));
        }
    }

    //initalizing validator arrays to false
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension + 1; j++) {
            row[i][j] = false;
            col[i][j] = false;
        } 
    } 

    //initalizing validator box matrix to false
    for (int i = 0; i < sqrtDimension; i++) {
        for (int j = 0; j < sqrtDimension; j++) {
            for (int k = 0; k < dimension + 1; k++) {
                boxes[i][j][k] = false;
            } 
        } 
    } 

    // set each matrix to its appropriate struct property
    val -> row = row;
    val -> col = col;
    val -> boxes = boxes;
    val -> dimension = dimension;

    return val;
}

/*********** validator_getRow **************/
/*
 * see validator.h for more information
 */
bool ** validator_getRow(validator_t* val) {
    if (val != NULL) {
        return val -> row;
    }
    return NULL;
}

/*********** validator_getCol **************/
/*
 * see validator.h for more information
 */
bool** validator_getCol(validator_t* val) {
    if (val != NULL) {
        return val -> col;
    }
    return NULL;
}

/*********** validator_getBoxes **************/
/*
 * see validator.h for more information
 */
bool*** validator_getBoxes(validator_t* val) {
    if (val != NULL) {
        return val -> boxes;
    }
    return NULL;
}

/*********** validator_delete **************/
/*
 * see validator.h for more information
 */
void validator_delete(validator_t* val) {
    // retrieve the matrices from the struct
    bool** row = val -> row;
    bool** col = val -> col;
    bool*** boxes = val -> boxes;
    int dimension = val -> dimension;

    // free the row and column inner-arrays
    for (int i = 0; i < dimension; i++) {
        free(row[i]);
        free(col[i]);
    }

    int sqrtDimension = (int) sqrt(dimension);

    // free the boxes inner arrays
    for (int i = 0; i < sqrtDimension; i++) {
        for (int j = 0; j < sqrtDimension; j++) {
            free(boxes[i][j]);
        }
        free(boxes[i]);
    }

    // free everything else
    free(row);
    free(col);
    free(boxes);
    free(val);
}