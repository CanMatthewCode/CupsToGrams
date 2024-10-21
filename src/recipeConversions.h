#ifndef RECIPECONVERSIONS_H
#define RECIPECONVERSIONS_H

#include "ingredientConversions.h"
#define MAX_INGREDIENT_NUMBER 60
#define MAX_INGREDIENT_TEXT 1000

enum recipeType{
	APPETIZER,
	BAKED_GOOD,
	BREAKFAST,
	DESSERT,
	MAINS,
	SIDES,
	SNACKS,
	SOUPS
};

struct ingredientStruct{
	char ingredientName[INGREDIENT_BUFFER_LEN];
	char userCupsInput[INGREDIENT_BUFFER_LEN];
	float ingredientGrams;
};

struct recipeStruct{
	char recipeName [INGREDIENT_BUFFER_LEN];
	struct ingredientStruct ingredients[MAX_INGREDIENT_NUMBER];
	int numberOfIngredients;
	char recipeInstructions [MAX_INGREDIENT_NUMBER][MAX_INGREDIENT_TEXT];
	int numberOfInstructions;
	char recipeNotes [MAX_INGREDIENT_NUMBER][MAX_INGREDIENT_TEXT];
	int numberOfNotes;
	enum recipeType recipeType;
	struct recipeStruct *prev;
	struct recipeStruct *next;
};

/********************************************************************************************************************
* 																													*
*	  			creates new recipeStruct node, returns NULL on failure				 								*
*																													*
*********************************************************************************************************************/
struct recipeStruct *createNewRecipeNode(void);



#endif //RECIPECONVERSIONS_H