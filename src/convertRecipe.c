#include <stdio.h>
#include <ctype.h>
#include "convertRecipe.h"
#include "ingredientItemLinkedList.h"
#include "ingredientConversions.h"


/********************************************************************************************************************
* 																													*
*	  			text 								*
*																													*
*********************************************************************************************************************/

/*
1	Function to add new recipe
2	Function to add new ingredient
3	Function to add new note
4	Function to add new direction
5	Function to remove each (ingredient, note, direction)
6	Function to modify each (ingredient, note, direction, order of (ingredient, note, direction))
7	Function to display recipe in current state
8	Function to pretty print recipe to pdf
9	Function to store recipes in txt files
10	Function to retrieve recipes from txt files
11	Function to delete recipe
12	Function to search for recipe
13	Function to free all recipes calloc()ed on quite


*/

/********************************************************************************************************************
* 																													*
*	  			creates new recipeStruct node, returns NULL on failure				 								*
*																													*
*********************************************************************************************************************/
struct recipeStruct *createNewRecipe(void){
	struct recipeStruct newRecipe = calloc(1, sizeof(struct recipeStruct));
	if (newRecipe = NULL){
		perror("Failure to allocate memory for newRecipe node");
		return NULL;
	}
	return newRecipe;
}

/********************************************************************************************************************
* 																													*
*	  			add new ingredientStruct into newRecipe struct. Returns 1 on success, 0 on failure					*
*																													*
*********************************************************************************************************************/
int addNewIngredient(struct recipeStruct *newRecipe, struct ingredientType *head){
	char buffer[INGREDIENT_BUFFER_LEN];
	printf("\t\tEnter Ingredient Name To Add: ");
	readUserInputIntoBuffer(buffer);
	printf("\t\tEnter Ingredient Amount In Cups: ");
	
	//ask user for ingredient name readUserInputIntoBuffer()
	//find ingredient - store pointer to ingredient findIngredientItemNode() name stored in ingredientName[]
	//ask for user input for amount - getCups() stored in userCupsInput
	//use ingredient node to calculate amount of ingredient in recipe cupsToGrams(getCups value, findIngredientItemNode->gramsPerCup), store in ingredientGrams
	//
}
