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
*	 			check user input key against existing ingredientItem lists											*
*				accepts an ingredientType pointer as a 3rd argument to allow an out parameter when the matches'		*
*				head node is needed. Enter NULL as 3rd parameter if ingredientType pointer is not wanted 			*
*				returns pointer to ingredientItem node found on success, NULL on failure							*
*																													*
*********************************************************************************************************************/
struct ingredientItem *findIngredientItemNode(struct ingredientType *head, char buffer[INGREDIENT_BUFFER_LEN], struct ingredientType **ingredientTypeNode);

/********************************************************************************************************************
* 																													*
*	 			add a new node into the ingredientItem linked-list alphabetically									*
*				returns pointer to head on success, NULL on failure													*
*																													*
*********************************************************************************************************************/
struct ingredientItem *addNewIngredientItemNode(char buffer[INGREDIENT_BUFFER_LEN]);

/********************************************************************************************************************
* 																													*
*	 			puts an ingredientItem node into the ingredientItem linked-list alphabetically						*
*				returns pointer to head on success, NULL on failure													*
*																													*
*********************************************************************************************************************/
void placeIngredientItemNode(struct ingredientItem *ingredientItemNodeToAdd, struct ingredientType *nodeToAddsIngredientTypeNode);

/********************************************************************************************************************
* 																													*
*	 			modifies the ingredientName in an existing ingredientType node in the linked-list 					*
*																													*
*********************************************************************************************************************/
void modifyIngredientItemNodeName(struct ingredientItem *node);

/********************************************************************************************************************
* 																													*
*	 			modifies the cupsPerGram amount in an existing ingredientType node in the linked-list 				*
*																													*
*********************************************************************************************************************/
void modifyIngredientItemNodeWeight(struct ingredientItem *node);

/********************************************************************************************************************
* 																													*
*	 			modifies the tablespoonFlag in an existing ingredientType node in the linked-list 					*
*																													*
*********************************************************************************************************************/
void modifyIngredientItemNodeFlag(struct ingredientItem *node);

/********************************************************************************************************************
* 																													*
*	 			modify a value in an existing node in the ingredientItem linked-list 								*
*				modifies values on success, NULL on failure															*
*																													*
*********************************************************************************************************************/
void modifyIngredientItemNode(struct ingredientItem *node);

/********************************************************************************************************************
* 																													*
*	 			print the information stored in an ingredientItem node 				 								*
*																													*
*********************************************************************************************************************/
void printIngredientItemNode(struct ingredientItem *node);

/********************************************************************************************************************
* 																													*
*	 			prints all the ingredientItem nodes stored in the head member of an ingredientType node 			*
*																													*
*********************************************************************************************************************/
void printAllIngredientItemNodes(struct ingredientType *node);

/********************************************************************************************************************
* 																													*
*	 			delete an ingredientItem node						 				 								*
*				accepts the ingredientItem node to be deleted and it's attached ingredientType node as parameters	*
*				returns 0 on success, 1 on cancel													*
*																													*
*********************************************************************************************************************/
int deleteIngredientItemNode(struct ingredientItem *node, struct ingredientType *headNode);

#endif //INGREDIENTITEMLINKEDLIST_H