#include <stdio.h>
#include <string.h>
#include "recipeConversions.h"
#include "ingredientConversions.h"
#include "recipeLinkedList.h"
#include "recipePrintFunctions.h"

/********************************************************************************************************************
* 																													*
*			  	prints a recipe's name surrounded by ***s on top, bottom, and sides									*
*																													*
*********************************************************************************************************************/
void printRecipeName(struct recipeStruct *recipe){
	int nameSize = strlen(recipe->recipeName);
	puts("\n");
	puts("\t\t*********************************************************************************");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	printf("\t\t*");
	for (int i = 0; i < ((79 - nameSize) / 2); i++)
		printf(" ");
	printf("%s", recipe->recipeName);
	for (int i = 0; i < ((79 - nameSize) / 2); i++)
		printf(" ");
	if (((79 - nameSize) % 2) == 1)
		printf(" ");
	printf("*\n");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*********************************************************************************");
}

/********************************************************************************************************************
* 																													*
*	  			prints a recipeStruct's ingredients in a listed order												*
*																													*
*********************************************************************************************************************/
void printRecipeIngredients(struct recipeStruct *recipe){
	char ingredientGramsPrintBuffer[10] = {'\0'};
	puts("\n\n\t\t\tINGREDIENTS:\n");
	for (int i = 0; i < recipe->numberOfIngredients; i++){
		memset(ingredientGramsPrintBuffer, 0, sizeof(ingredientGramsPrintBuffer));
		decimalPlaceCheck(recipe->ingredients[i].ingredientGrams, ingredientGramsPrintBuffer);
		if (recipe->ingredients[i].nonWeighedIngredientFlag == 1){
			if (i < 9){
				if (recipe->ingredients[i].ingredientGrams == 0){
					printf("\t\t%d)\t    %s ", i + 1, recipe->ingredients[i].ingredientName);
					if (strlen(recipe->ingredients[i].userCupsInput) > 0)
						printf("(%s)\n", recipe->ingredients[i].userCupsInput);
					else (printf("\n"));
				} else {
					printf("\t\t%d)  %s %s ", i + 1, ingredientGramsPrintBuffer, recipe->ingredients[i].ingredientName);
					if (strlen(recipe->ingredients[i].userCupsInput) > 0)
						printf("(%s)\n", recipe->ingredients[i].userCupsInput);
					else (printf("\n"));
				}
			} else {
				if (recipe->ingredients[i].ingredientGrams == 0){
					printf("\t\t%d)\t   %s ", i + 1, recipe->ingredients[i].ingredientName);
					if (strlen(recipe->ingredients[i].userCupsInput) > 0)
						printf("(%s)\n", recipe->ingredients[i].userCupsInput);
					else (printf("\n"));
				} else {
					printf("\t\t%d) %s %s ", i + 1, ingredientGramsPrintBuffer, recipe->ingredients[i].ingredientName);
					if (strlen(recipe->ingredients[i].userCupsInput) > 0)
						printf("(%s)\n", recipe->ingredients[i].userCupsInput);
					else (printf("\n"));
				}
			}
		} else if (i < 9){
			if (recipe->ingredients[i].ingredientGrams == 1)
				printf("\t\t%d)  %s Gram Of %s ", i + 1, ingredientGramsPrintBuffer, recipe->ingredients[i].ingredientName);
			else
				printf("\t\t%d)  %s Grams Of %s ", i + 1, ingredientGramsPrintBuffer, recipe->ingredients[i].ingredientName);
			if (strlen(recipe->ingredients[i].userCupsInput) > 0)
				printf("(%s)\n", recipe->ingredients[i].userCupsInput);
			else (printf("\n"));
		} else {
			if (recipe->ingredients[i].ingredientGrams == 1)
				printf("\t\t%d) %s Gram Of %s ", i + 1, ingredientGramsPrintBuffer, recipe->ingredients[i].ingredientName);
			else
				printf("\t\t%d) %s Grams Of %s ", i + 1, ingredientGramsPrintBuffer, recipe->ingredients[i].ingredientName);
			if (strlen(recipe->ingredients[i].userCupsInput) > 0)
				printf("(%s)\n", recipe->ingredients[i].userCupsInput);
			else (printf("\n"));
		}
	}
	printf("\n\n");
}

/********************************************************************************************************************
* 																													*
*	  			prints a recipeStruct's instructions in a listed order												*
*																													*
*********************************************************************************************************************/
void printRecipeInstructions(struct recipeStruct *recipe){
	puts("\n\n\t\t\tINSTRUCTIONS:\n");
	for (int i = 0; i < recipe->numberOfInstructions; i++)
		printf("\t\t%d)  %s\n", i + 1, recipe->recipeInstructions[i]);
	printf("\n\n");
}

/********************************************************************************************************************
* 																													*
*			  	prints a recipeStruct's notes in a listed order														*
*																													*
*********************************************************************************************************************/
void printRecipeNotes(struct recipeStruct *recipe){
	puts("\n\n\t\t\tNOTES:\n");
	for (int i = 0; i < recipe->numberOfNotes; i++)
		printf("\t\t%d)  %s\n", i + 1, recipe->recipeNotes[i]);
}

/********************************************************************************************************************
* 																													*
*			  	prints a recipeStruct's recipeType enum as a string													*
*																													*
*********************************************************************************************************************/
void printRecipeType(struct recipeStruct *recipe){
	char enumValue[12] = {'\0'};
	switch (recipe->recipeType){
		case 0:		strcpy(enumValue, "APPETIZER");
					break;
		case 1:		strcpy(enumValue, "BAKED GOOD");
					break;
		case 2:		strcpy(enumValue, "BREAKFAST");
					break;
		case 3:		strcpy(enumValue, "DESSERT");
					break;
		case 4:		strcpy(enumValue, "LUNCH");
					break;
		case 5:		strcpy(enumValue, "ENTREE");
					break;
		case 6:		strcpy(enumValue, "SIDE DISH");
					break;
		case 7:		strcpy(enumValue, "SNACK");
					break;
		case 8:		strcpy(enumValue, "SOUP");
					break;
		default:	break;
	}
	printf("\t\t%81s", enumValue);
}

/********************************************************************************************************************
* 																													*
*	 		 	prints the entirety of a recipeStruct's contents in a recipe-like manor								*
*																													*
*********************************************************************************************************************/
void printFullRecipe(struct recipeStruct *recipe){
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	if (recipe->numberOfInstructions > 0)
		printRecipeInstructions(recipe);
	if (recipe->numberOfNotes > 0)
		printRecipeNotes(recipe);
	puts("\n\n\n\n\n\n");
	printRecipeType(recipe);
	puts("\n\n\t\t*********************************************************************************");
}

/********************************************************************************************************************
* 																													*
*	 		 	prints the entirety of a recipeStruct's contents in a recipe-like manor								*
*				with the option to print the recipe to PDF															*
*																													*
*********************************************************************************************************************/
void printFullRecipeWithPDFOption(struct recipeStruct *recipe){
	char ch = '\0';
	printFullRecipe(recipe);
	printf("\n\n\n\n\n\t\t(P) Print To PDF\t\t\t\tOr Press Enter To Continue ");
	do {
		ch = toupper(getchar());
		if (ch == 'P'){
			printRecipeToPDF(recipe);
			printFullRecipe(recipe);
			printf("\n\n\n\n\n\t\tPress Enter To Continue ");
			while ((ch = getchar()) != '\n');
			ch = '\0';
		}
	} while (ch != '\n');
}

/********************************************************************************************************************
* 																													*
*	 			prints the names of all the nodes in the recipeStruct linked-list alphabetically					*
*																													*
*********************************************************************************************************************/
void printAllRecipeNames(struct recipeStruct *recipeHead){
	struct recipeStruct *cur = NULL;
	struct recipeStruct *foundRecipe = NULL;
	clearScreen();
	puts("\n\n\t\t*********************************************************************************");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*\t\t\t  -ALL RECIPES AVAILABLE-       \t\t\t*");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*********************************************************************************\n\n");
	printf("\t\t");
	int numberOfCharactersOnLine = NUMBER_OF_CHARS_ON_SCREEN;
	int curNameLength = 0;
	int nextNameLength = 0;
	for (cur = recipeHead; cur; cur = cur->next){
		curNameLength = strlen(cur->recipeName);
		printf("%s        ", cur->recipeName);
		numberOfCharactersOnLine -= (curNameLength + 8);
		if (cur->next)
			nextNameLength = strlen(cur->next->recipeName);
		if (numberOfCharactersOnLine - nextNameLength < 1){
			printf("\n\n\n\t\t");
			numberOfCharactersOnLine = NUMBER_OF_CHARS_ON_SCREEN;
		}
	}
	printf("\n\n\n\n\n\t\tEnter Name To View Recipe, Or Hit Enter To Continue: ");
	char ch = '\0';
	if  ((ch = getchar()) == '\n') {
		return;
	} else {
		ungetc(ch, stdin);
		char recipeNameBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
		readUserInputIntoBuffer(recipeNameBuffer);
		foundRecipe = findRecipe(recipeHead, recipeNameBuffer);
		if (foundRecipe)
			printFullRecipeWithPDFOption(foundRecipe);
	}
}

/********************************************************************************************************************
* 																													*
*	  			prints all recipe nodes of a chosen food type						 								*
*																													*
*********************************************************************************************************************/
void printRecipeByType (struct recipeStruct *headPointer){
	struct recipeStruct *cur = headPointer;
	clearScreen();
	puts("\n\n\t\t*********************************************************************************");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*\t\t\t  -SHOW RECIPE NAMES BY FOOD TYPE-       \t\t*");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*********************************************************************************\n\n");
	int choice = 0;
	puts("\n\n\t\t(1) APPETIZER\t\t(2) BAKED GOOD\t\t(3) BREAKFAST\t\t(4) DESSERT\n\n\t\t(5) LUNCH\t\t(6) ENTREE\t\t(7) SIDE DISH\t\t(8) SNACK\n\n\t\t(9) SOUP");
	printf("\n\n\t\tEnter Number(#) Of Food Type To Print: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > 9)
			printf("\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > 9);
	printf("\n\n\t\t");
	int numberOfCharactersOnLine = NUMBER_OF_CHARS_ON_SCREEN;
	int curNameLength = 0;
	int nextNameLength = 0;
	for (; cur; cur = cur->next){
		if (cur->recipeType == (choice - 1)){
			curNameLength = strlen(cur->recipeName);
			printf("%s        ", cur->recipeName);
			numberOfCharactersOnLine -= (curNameLength + 8);
			if (cur->next)
				nextNameLength = strlen(cur->next->recipeName);
			if (numberOfCharactersOnLine - nextNameLength < 1){
				printf("\n\n\n\t\t");
				numberOfCharactersOnLine = NUMBER_OF_CHARS_ON_SCREEN;
			}
		}
	}
	printf("\n\n\n\n\n\t\tEnter Name To View Recipe, Or Hit Enter To Continue: ");
	struct recipeStruct *foundRecipe = NULL;
	char ch = '\0';
	if  ((ch = getchar()) == '\n') {
		return;
	} else {
		ungetc(ch, stdin);
		char recipeNameBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
		readUserInputIntoBuffer(recipeNameBuffer);
		foundRecipe = findRecipe(headPointer, recipeNameBuffer);
		if (foundRecipe)
			printFullRecipeWithPDFOption(foundRecipe);
	}
}
