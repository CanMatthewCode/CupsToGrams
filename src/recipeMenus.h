#ifndef RECIPEMENUS_H
#define RECIPEMENUS_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "recipeConversions.h"
#include "recipeLinkedList.h"
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"

/************************************************************************************************************
* 																											*
*				menu function for all recipe functions														*
*				returns a pointer to the recipeStruct linked list head										*
*																											*
*************************************************************************************************************/
struct recipeStruct *recipeMenus(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

/************************************************************************************************************
* 																											*
*				menu for editing an already filled in recipeStruct 											*
*				returns a pointer to the recipeStruct linked list head in case of delete recipe				*
*																											*
*************************************************************************************************************/
struct recipeStruct *editRecipeMenu(struct recipeStruct *recipe, struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

/************************************************************************************************************
* 																											*
*				menu for modifying a recipeStruct's ingredients 											*
*																											*
*************************************************************************************************************/
void editRecipeIngredientsMenu(struct recipeStruct *recipe, struct ingredientType *ingredientHead);

/************************************************************************************************************
* 																											*
*				menu for modifying a recipeStruct's instructions 											*
*																											*
*************************************************************************************************************/
void editRecipeInstructionsMenu(struct recipeStruct *recipe);

/************************************************************************************************************
* 																											*
*				menu for modifying a recipeStruct's notes		 											*
*																											*
*************************************************************************************************************/
void editRecipeNotesMenu(struct recipeStruct *recipe);

/************************************************************************************************************
* 																											*
*				menu for modifying or deleting an existing recipe in the recipeStruct linked list			*
*				returns a pointer to the recipeStruct linked list head in case of delete recipe				*
*																											*
*************************************************************************************************************/
struct recipeStruct *modifyExistingRecipeMenu(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

/************************************************************************************************************
* 																											*
*				menu function for printing all recipes, printing by type, or find recipe to print			*
*				returns a pointer to the recipeStruct linked list head in case of delete recipe				*
*																											*
*************************************************************************************************************/
struct recipeStruct *printSavedRecipeMenus(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

#endif //RECIPEMENUS_H
