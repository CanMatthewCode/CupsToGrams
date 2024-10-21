#include <stdio.h>
#include <ctype.h>
#include "recipeConversions.h"
#include "ingredientItemLinkedList.h"
#include "ingredientConversions.h"


/********************************************************************************************************************
* 																													*
*	  			creates new recipeStruct node, returns NULL on failure				 								*
*																													*
*********************************************************************************************************************/
struct recipeStruct *createNewRecipeNode(void){
	struct recipeStruct *newRecipe = calloc(1, sizeof(struct recipeStruct));
	if (newRecipe == NULL){
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
int addNewIngredient(struct recipeStruct *currentRecipe, struct ingredientType *head){
	struct ingredientItem *foundNewIngredient = NULL;
	char buffer[INGREDIENT_BUFFER_LEN];
	char cupsInputAmountBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	printf("\t\tWhat Ingredient Would You Like To Add?: ");
	readUserInputIntoBuffer(buffer);
	if ((foundNewIngredient = findIngredientItemNode(head, buffer, NULL)) == NULL)
		return 0;
	else {
		puts("\t\tEnter Amount To Add In Cups Notation: ");
		readUserInputIntoBuffer(cupsInputAmountBuffer);
		strcpy(currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientName, foundNewIngredient->ingredientName);
		strcpy(currentRecipe->ingredients[currentRecipe->numberOfIngredients].userCupsInput, cupsInputAmountBuffer);
		currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams = cupsToGrams(cupsInputAmountBuffer, foundNewIngredient);
	}
	return 1;
}

