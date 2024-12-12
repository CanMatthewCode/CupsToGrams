#ifndef RECIPELINKEDLIST_H
#define RECIPELINKEDLIST_H

#include <stdio.h>
#include "ingredientConversions.h"
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

/********************************************************************************************************************
* 																													*
*	 			add a new node into the recipeStruct linked-list alphabetically										*
*				returns pointer to head on success, NULL on failure													*
*																													*
*********************************************************************************************************************/
struct recipeStruct *placeRecipeStructNode(struct recipeStruct *recipeHead, struct recipeStruct *newRecipe);

/********************************************************************************************************************
* 																													*
*	  			finds a recipe in the recipeStruct linked list by parsing a buffer to find comparable names			*
*				returns NULL if no recipe with a partially matching name is found									*
*																													*
*********************************************************************************************************************/
struct recipeStruct *findRecipe(struct recipeStruct *recipeHead, char buffer[INGREDIENT_BUFFER_LEN]);

/**********************************************************************************************************v*********
* 																													*
*	 			delete recipe permanently from recipe linked-list													*
*				returns recipeType pointer to head on success, NULL on failure or cancel							*
*																													*
*********************************************************************************************************************/
struct recipeStruct *deleteFullRecipeNode(struct recipeStruct *head, struct recipeStruct *recipeToDelete);

/********************************************************************************************************************
* 																													*
*	 			free full recipeStruct linked-list from memory														*
*																													*
*********************************************************************************************************************/
void freeRecipeStructList(struct recipeStruct *head);

#endif //RECIPELINKEDLIST_H
