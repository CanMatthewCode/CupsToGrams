#ifndef RECIPEMENUS_H
#define RECIPEMENUS_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "recipeConversions.h"
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"

/************************************************************************************************************
* 																											*
*				menu function for all recipe functions														*
*																											*
*************************************************************************************************************/
struct recipeStruct *recipeMenus(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

/************************************************************************************************************
* 																											*
*				menu for adding new recipe functions, returns pointer to newly added recipe					*
*																											*
*************************************************************************************************************/
struct recipeStruct *convertNewRecipe(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

/************************************************************************************************************
* 																											*
*				menu for editing an already filled in recipeStruct 											*
*																											*
*************************************************************************************************************/
void editRecipeMenu(struct recipeStruct *recipe, struct ingredientType *ingredientHead);

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

#endif //RECIPEMENUS_H