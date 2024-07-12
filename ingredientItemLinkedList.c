#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "ingredientconversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"

/*		Load from text file sub-ingredientItemLinkedList for each opened ingredientTypeNode named [buffername].txt
*		Check if wanted ingredientType exists already in node
*		Create new node for ingredientTypeLinkedList
*		Populate and Add new node to ingredientItemLinkedList
*		Delete selected node
*		Print ingredient node list
*		Dump ingredientTypeLinkedList into text file named ingredientType->ingredientName
*		Free ingredientTypeLinkedList 
*/

/************************************************************************************************************
* 																											*
*	  	loadIngredientItem loads the ingredientsItems linked-list associated with an ingredientType pointer *
*		loads a .txt file from the typeName buffer in the ingredientType struct								*
*		returns a pointer to ingredientItem link-list head on success, NULL on failure						*
*																											*
*************************************************************************************************************/
struct ingredientItem *loadIngredientItem(struct ingredientType *node){

}