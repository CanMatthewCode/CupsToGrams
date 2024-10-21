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

#endif //RECIPEMENUS_H