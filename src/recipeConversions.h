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
	LUNCH,
	ENTREE,
	SIDE,
	SNACK,
	SOUP
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

/********************************************************************************************************************
* 																													*
*	  			add new ingredientStruct into newRecipe struct. increases numberOfIngredients on success			*
*																													*
*********************************************************************************************************************/
void addNewIngredient(struct recipeStruct *currentRecipe, struct ingredientType *head);

/********************************************************************************************************************
* 																													*
*	  			add new instruction into recipeStruct. increases numberOfInstruction on success						*
*																													*
*********************************************************************************************************************/
void addNewInstruction(struct recipeStruct *currentRecipe);

/********************************************************************************************************************
* 																													*
*	  			add new note into recipeStruct. Increases numberOfNotes on success									*
*																													*
*********************************************************************************************************************/
void addNewNote(struct recipeStruct *currentRecipe);

/********************************************************************************************************************
* 																													*
*	  			set enum recipeType type to: 	APPETIZER, BAKED_GOOD, BREAKFAST, DESSERT, MAINS,					*
*												SIDES, SNACKS, SOUPS.  												*
*				return 1 on success 0 on failure																	*
*																													*
*********************************************************************************************************************/
void setRecipeType(struct recipeStruct *currentRecipe);

/********************************************************************************************************************
* 																													*
*	  			used to fill in a recipeDirection or recipeNote field of a recipeStruct								*
*																													*
********************************************************************************************************************/
void readUserInputIntoRecipe(char directionsBuffer[MAX_INGREDIENT_TEXT]);

/********************************************************************************************************************
* 																													*
*	  			prints a recipe's name surrounded by *** on top, bottom, and sides									*
*																													*
*********************************************************************************************************************/
void printRecipeName(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			prints a recipeStruct's ingredients in a listed order												*
*																													*
*********************************************************************************************************************/
void printRecipeIngredients(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			prints a recipeStruct's instructions in a listed order												*
*																													*
*********************************************************************************************************************/
void printRecipeInstructions(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			prints a recipeStruct's notes in a listed order														*
*																													*
*********************************************************************************************************************/
void printRecipeNotes(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			prints the entirety of a recipeStruct's contents in a recipe-like manor								*
*																													*
*********************************************************************************************************************/
void printFullRecipe(struct recipeStruct *recipe);


#endif //RECIPECONVERSIONS_H