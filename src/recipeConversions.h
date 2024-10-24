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
	int numberOfIngredients;
	struct ingredientStruct ingredients[MAX_INGREDIENT_NUMBER];
	int numberOfInstructions;
	char recipeInstructions [MAX_INGREDIENT_NUMBER][MAX_INGREDIENT_TEXT];
	int numberOfNotes;
	char recipeNotes [MAX_INGREDIENT_NUMBER][MAX_INGREDIENT_TEXT];
	enum recipeType recipeType;
	struct recipeStruct *prev;
	struct recipeStruct *next;
};

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
*			  	prints a recipeStruct's recipeType enum as a string													*
*																													*
*********************************************************************************************************************/
void printRecipeType(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			prints the entirety of a recipeStruct's contents in a recipe-like manor								*
*																													*
*********************************************************************************************************************/
void printFullRecipe(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			modifies the recipe's name in a recipeStruct														*
*																													*
*********************************************************************************************************************/
void modifyRecipeName(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			modifies the amount of an ingredient in a recipeStruct's ingredient's array							*
*																													*
*********************************************************************************************************************/
void modifyIngredientAmount(struct recipeStruct *recipe, struct ingredientType *ingredientHead);

/********************************************************************************************************************
* 																													*
*	  			reorders the ingredients in a recipeStruct's ingredient's array										*
*																													*
*********************************************************************************************************************/
void modifyIngredientOrder(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			deletes an ingredients from a recipeStruct's ingredients array										*
*																													*
*********************************************************************************************************************/
void deleteIngredientFromRecipe(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			modifies an instruction in a recipeStruct's instructions array										*
*																													*
*********************************************************************************************************************/
void modifyInstruction(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			reorders the instructions in a recipeStruct's instructions array									*
*																													*
*********************************************************************************************************************/
void modifyInstructionOrder(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			deletes an instruction from a recipeStruct's instructions array										*
*																													*
*********************************************************************************************************************/
void deleteInstructionFromRecipe(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			modifies an instruction in a recipeStruct's notes array												*
*																													*
*********************************************************************************************************************/
void modifyNote(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			reorders the notes in a recipeStruct's notes array													*
*																													*
*********************************************************************************************************************/
void modifyNoteOrder(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			deletes a note in a recipeStruct's notes array														*
*																													*
*********************************************************************************************************************/
void deleteNoteFromRecipe(struct recipeStruct *recipe);

#endif //RECIPECONVERSIONS_H