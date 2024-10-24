#ifndef RECIPELINKEDLIST_H
#define RECIPELINKEDLIST_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"
#include "recipeConversions.h"

/********************************************************************************************************************
* 																													*
*	  			creates new recipeStruct node, returns NULL on failure				 								*
*																													*
*********************************************************************************************************************/
struct recipeStruct *createNewRecipeNode(void);

/********************************************************************************************************************
* 																													*
*	  			dumps all recipeStruct nodes to text files, returns 0 on success, -1 on failure						*
*																													*
*********************************************************************************************************************/
int dumpRecipesFromLinkedList(struct recipeStruct *recipeHead);

/********************************************************************************************************************
* 																													*
*	  			loadRecipes loads the recipes into a linked-list from a recipes.txt file							*
*				returns a pointer to recipe link-list head on success, NULL on failure								*
*																													*
*********************************************************************************************************************/
struct recipeStruct *loadRecipesToLinkedList(void);

#endif //RECIPELINKEDLIST_H