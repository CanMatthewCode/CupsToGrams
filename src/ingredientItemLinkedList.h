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
struct ingredientItem *findIngredientItemNode(struct ingredientType *head, char buffer[INGREDIENT_BUFFER_LEN]);

/********************************************************************************************************************
* 																													*
*	 			add a new node into the ingredientItem linked-list alphabetically									*
*				returns pointer to head on success, NULL on failure													*
*																													*
*********************************************************************************************************************/
struct ingredientItem *addNewIngredientItemNode(struct ingredientItem *head, char buffer[INGREDIENT_BUFFER_LEN]);

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
*	 			delete a an ingredientItem node						 				 								*
*				returns 0 on success, 1 on cancel,  -1 on failure																	*
*																													*
*********************************************************************************************************************/
int deleteIngredientItemNode(struct ingredientType *head, char buffer[INGREDIENT_BUFFER_LEN]);

#endif //INGREDIENTITEMLINKEDLIST_H