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

/********************************************************************************************************************
* 																													*
*	  			set enum recipeType type to: 	APPETIZER, BAKED_GOOD, BREAKFAST, DESSERT, MAINS,					*
*												SIDES, SNACKS, SOUPS.  												*
*				return 1 on success 0 on failure																	*
*																													*
*********************************************************************************************************************/
void setRecipeType(struct recipeStruct *currentRecipe){
	currentRecipe->recipeType = 0;
	int choice = 0;
	puts("\t\t(1) APPETIZER\t(2) BAKED GOOD\t(3) BREAKFAST\t(4) DESSERT\n\n\t\t(5) MAINS\t\t(6) SIDES\t\t(7) SNACKS\t\t(8)SOUPS");
	printf("\n\n\t\tEnter Number(#) Of Food Type: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > 8)
			printf("\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > 8);
	currentRecipe->recipeType = choice - 1;
}

/************************************************************************************************************
* 																											*
*	  	used to fill in a recipeDirection or recipeNote field of a recipeStruct								*
*																											*
*************************************************************************************************************/
void readUserInputIntoRecipe(char directionsBuffer[MAX_INGREDIENT_TEXT]){
	char *temp = directionsBuffer;
	char ch = '\0';
	int counter = 0;
	do{
	    ch = getchar();
	    if ((counter == 0) && (ch == '\n'))
    	    printf("\t\tInvalid Entry: ");
    } while (ch == '\n');
	while ((ch == ' ') || (ch == '\t') || (ch == '\n'))
		ch = getchar();
	ch = toupper(ch);
	*temp = ch;
	counter = 1;
	while ((ch = getchar()) != '\n' && counter < (MAX_INGREDIENT_TEXT - 1)){
		ch = tolower(ch);
		if (ch == '\t')
		    ch = ' ';
		if (((ch == ' ') || (ch == '\t')) && ((*(temp+counter-1) == ' ')))
			continue;
		//capitalize first letter of new sentence
		if (((*(temp+counter-1) == ' ') && (*(temp+counter-2) == '.')) || ((*(temp+counter-1) == ' ') && (*(temp+counter-2) == '?')))
			ch = toupper(ch);
		//capitalize I when it stands alone
		if ((ch == ' ') && (*(temp+counter-1) == 'i') && (*(temp+counter-2) == ' '))
		    *(temp+counter-1) = 'I';
		*(temp+counter) = ch;
		counter++;
	}
	if (*(temp+counter) == ' ')
		*(temp+counter) = '\0';  
}

/************************************************************************************************************
* 																											*
*	  	prints a recipe's name surrounded by ***s on top, bottom, and sides									*
*																											*
*************************************************************************************************************/
void printRecipeName(struct recipeStruct *recipe){
	int nameSize = strlen(recipe->recipeName);
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

/************************************************************************************************************
* 																											*
*	  	prints a recipeStruct's ingredients in a listed order												*
*																											*
*************************************************************************************************************/
void printRecipeIngredients(struct recipeStruct *recipe){
	puts("\n\n\t\tINGREDIENTS:\n\n");
	for (int i = 0; i < recipe->numberOfIngredients; i++)
		printf("\t\t%d)  %7.2f grams of %s (%s)\n", i + 1, recipe->ingredients[i].ingredientGrams, recipe->ingredients[i].ingredientName, recipe->ingredients[i].userCupsInput);
}

/************************************************************************************************************
* 																											*
*	  	prints a recipeStruct's instructions in a listed order												*
*																											*
*************************************************************************************************************/
void printRecipeInstructions(struct recipeStruct *recipe){
	puts("\n\n\t\tINSTRUCTIONS:\n\n");
	for (int i = 0; i < recipe->numberOfInstructions; i++)
		printf("\t\t%d)  %s\n", i + 1, recipe->recipeInstructions[i]);
}

/************************************************************************************************************
* 																											*
*	  	prints a recipeStruct's notes in a listed order														*
*																											*
*************************************************************************************************************/
void printRecipeNotes(struct recipeStruct *recipe){
	puts("\n\n\t\tNOTES:\n\n");
	for (int i = 0; i < recipe->numberOfNotes; i++)
		printf("\t\t%d)  %s\n", i + 1, recipe->recipeNotes[i]);
}

/************************************************************************************************************
* 																											*
*	  	prints the entirety of a recipeStruct's contents in a recipe-like manor								*
*																											*
*************************************************************************************************************/
void printFullRecipe(struct recipeStruct *recipe){
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	if (recipe->numberOfInstructions > 0)
		printRecipeInstructions(recipe);
	if (recipe->recipeNotes > 0)
		printRecipeNotes(recipe);
}