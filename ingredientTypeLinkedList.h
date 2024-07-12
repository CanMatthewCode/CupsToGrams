#ifndef INGREDIENTTYPELINKEDLIST_H
#define INGREDIENTTYPELINKEDLIST_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "ingredientconversions.h"
#include "ingredientTypeLinkedList.h"

/************************************************************************************************************
* 																											*
*	  	loadIngredientTypes loads the ingredientsTypes linked-list from an IngredientTypes.txt file			*
*		returns a pointer to ingredientType link-list head on success, NULL on failure						*
*																											*
*************************************************************************************************************/
struct ingredientType *loadIngredientTypes(struct ingredientType *head);


/************************************************************************************************************
* 																											*
*	  	create a new node memory block with malloc for an ingredientType linked-list node	 				*
*		returns a pointer to the new memory block on success, NULL on failure								*
*																											*
*************************************************************************************************************/
struct ingredientType *createIngredientTypeNode(void);


/************************************************************************************************************
* 																											*
*	 	check user input key against existing ingredientTypes list											*
*		returns pointer to node found on success, NULL on failure											*
*																											*
*************************************************************************************************************/
struct ingredientType *findIngredientType(struct ingredientType *head, char buffer[INGREDIENT_BUFFER_LEN]);


/************************************************************************************************************
* 																											*
*	 	add a new node into the ingredientType linked-list alphabetically									*
*		returns pointer to newly inserted node on success, NULL on failure									*
*																											*
*************************************************************************************************************/
struct ingredientType *addNewIngredientTypeNode(struct ingredientType *head);


/************************************************************************************************************
* 																											*
*	 	print all ingredient types currently stored in the ingredientType linked-list head					*
*																											*
*************************************************************************************************************/
void printIngredientTypeList(struct ingredientType *head);


/************************************************************************************************************
* 																											*
*	 	dump the ingredient type names from linked-list into link IngredientTypes.txt file					*
*		returns -1 on failure to open IngredientTypes.txt file, return 0 on successful dump					*
*																											*
*************************************************************************************************************/
int dumpIngredientTypeList(struct ingredientType *head);


/************************************************************************************************************
* 																											*
*	 	free ingredientType linked-list from memory															*
*																											*
*************************************************************************************************************/
void freeIngredientTypeList(struct ingredientType *head);


/************************************************************************************************************
* 																											*
*	 	delete node permanently from ingredientType linked-list												*
*		returns ingredientType pointer to head on success, NULL on failure or cancel						*
*																											*
*************************************************************************************************************/
struct ingredientType *deleteIngredientTypeNode(struct ingredientType *head);


#endif (INGREDIENTTYPELINKEDLIST_H)