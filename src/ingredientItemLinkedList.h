#ifndef INGREDIENTITEMLINKEDLIST_H
#define INGREDIENTITEMLINKEDLIST_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"

/********************************************************************************************************************
* 																													*
*	  			create a new node memory block with calloc for an ingredientItem linked-list node		 			*
*				returns a pointer to the new memory block on success, NULL on failure								*
*																													*
*********************************************************************************************************************/
struct ingredientItem *createIngredientItemNode(void);

/************************************************************************************************************
* 																											*
*	  	loadIngredientItem loads the ingredientsItems linked-list associated with an ingredientType pointer *
*		loads a .txt file from the typeName buffer in the ingredientType struct								*
*		returns a pointer to ingredientItem link-list head on success, NULL on failure						*
*																											*
*************************************************************************************************************/
struct ingredientItem *loadIngredientItem(struct ingredientType *node);

/************************************************************************************************************
* 																											*
*	  	loadIngredientItem loads the ingredientsItems linked-list associated with an ingredientType pointer *
*		loads a .txt file from the typeName buffer in the ingredientType struct								*
*		returns a pointer to ingredientItem link-list head on success, NULL on failure						*
*																											*
*************************************************************************************************************/
struct ingredientType *loadAllIngredientTypeSubLists(struct ingredientType *head);

/********************************************************************************************************************
* 																													*
*	 			dump the ingredient item names from linked-list into link ingredientTypes->typeName.txt file		*
*				returns -1 on failure to open IngredientTypes.txt file, return 0 on successful dump					*
*																													*
*********************************************************************************************************************/
int dumpIngredientItemList(struct ingredientType *typeNode);

/********************************************************************************************************************
* 																													*
*	 			check user input key against existing ingredientItem list											*
*				returns pointer to node found on success, NULL on failure											*
*																													*
*********************************************************************************************************************/
struct ingredientItem *findIngredientItem(struct ingredientItem *head, char buffer[INGREDIENT_BUFFER_LEN]);


#endif //INGREDIENTITEMLINKEDLIST_H