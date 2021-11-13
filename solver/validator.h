/*
 * validator.h - header file for validator.c
 * 
 * Ethan Chen, Jeffrey Jiang, Bansharee Ireen
 * Nov 13, 2021
 * 
 * CS50, Fall 2021
 */

#ifndef __VALIDATOR
#define __VALIDATOR

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct validator validator_t;

/*********** validator_new **************/
/*
 * creates a new validator struct, mallocing all of the necessary memory
 * caller is responsible for later freeing this memory, typically by calling validator_delete
 * 
 * caller provides: a valid dimension
 */
validator_t* validator_new(int dimension);

/*********** validator_getRow **************/
/*
 * getter method to get the row matrix
 * 
 * caller provides: a valid validator pointer
 */
bool** validator_getRow(validator_t* val);

/*********** validator_getCol **************/
/*
 * getter method to get the col matrix
 * 
 * caller provides: a valid validator pointer
 */
bool** validator_getCol(validator_t* val);

/*********** validator_getBoxes **************/
/*
 * getter method to get the boxes matrix
 * 
 * caller provides: a valid validator pointer
 */
bool*** validator_getBoxes(validator_t* val);

/*********** validator_delete **************/
/*
 * deletes a previously created validator struct
 *
 * caller provides: a valid validator pointer
 */
void validator_delete(validator_t* val);

#endif