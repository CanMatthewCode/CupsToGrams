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
*																											*
*************************************************************************************************************/
struct recipeStruct *recipeMenus(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

/************************************************************************************************************
* 																											*
*				menu for editing an already filled in recipeStruct 											*
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
*																											*
*************************************************************************************************************/
struct recipeStruct *modifyExistingRecipeMenu(struct recipeStruct *recipeHeadPointer, struct ingredientType *ingredientHead);

/************************************************************************************************************
* 																											*
*				menu for finding recipe from the recipeStruct headPointer									*
*				and then printing chosen recipe out as a PDF document										*
*																											*
*************************************************************************************************************/
void printRecipeToPDFMenu(struct recipeStruct *recipeHeadPointer);

#endif //RECIPEMENUS_H