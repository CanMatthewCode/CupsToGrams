#include <stdio.h>
#include <ctype.h>
#include "recipeMenus.h"
#include "recipeConversions.h"
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"


/************************************************************************************************************
* 																											*
*				menu function for all recipe functions														*
*																											*
*************************************************************************************************************/
struct recipeStruct *recipeMenus(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead){
	char menu = '\0';
	struct recipeStruct *recipeHeadPointer = recipeHead;
//	struct ingredientType *ingredientHeadPointer = ingredientHead;
	clearScreen();
	do {
		clearScreen();
		puts("\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t      -CONVERT RECIPE- \t\t\t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		puts("\n\t\tMenu Options:\n");
	
		puts("\t\t(1) Convert New Recipe\n\t\t(2) Modify Recipe\n\t\t"
			 "(3) See Recipes By Type\n\t\t(4) Save a Recipe As A PDF\n\t\t"
			 "(B) Back");
		printf("\n\t\tEnter Selection: ");
		do {
        	menu = toupper(getchar());
        	if (menu == '\n'){
            	printf("\t\tInvalid Selection: ");
            	continue;
        	}
        	while (getchar() != '\n');
			if (strchr("1234B", menu) == NULL)
				printf("\t\tInvalid Selection: ");
		} while (strchr("1234B", menu) == NULL);
		switch (menu){
			case '1':	convertNewRecipe(recipeHead, ingredientHead);
						break;
			case '2':	//modifyExistingRecipeMenu()
						break;
			case '3':	//seeRecipesByType()
						break;
			case '4':	//saveRecipeToPDF()
						break;
			case 'B':	return recipeHeadPointer;
			default:	clearScreen();
						printf("\n\t\tInvalid Selection, Try Again\n");
		}
	} while (menu != 'B');
	return recipeHeadPointer;
}

/************************************************************************************************************
* 																											*
*				menu for adding new recipe functions, returns pointer to newly added recipe					*
*																											*
*************************************************************************************************************/
struct recipeStruct *convertNewRecipe(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead){
	char menu = '\0';
	char choice = '\0';
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	clearScreen();
	puts("\t\t*********************************************************************************");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*\t\t\t      -CONVERT NEW RECIPE- \t\t\t\t*");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*********************************************************************************");
	struct recipeStruct *recipeHeadPointer = recipeHead;
//	struct ingredientType *ingredientHeadPointer = ingredientHead;
	struct recipeStruct *newRecipe = createNewRecipeNode();
	do {
		printf("\n\n\t\tEnter New Recipe's Name: ");
		memset(buffer, 0, INGREDIENT_BUFFER_LEN);
		readUserInputIntoBuffer(buffer);
		printf("\n\n\t\t\t%s\n\n\n\t\tIs This Correct (y/n)? ", buffer);
		YESNOCHOICE(choice);
	} while (choice != 'Y');
	setRecipeType(newRecipe);
	choice = '\0';
	do {
		newRecipe->numberOfIngredients += addNewIngredient(newRecipe, ingredientHead);
		clearScreen();
		printFullRecipe(newRecipe);
		printf("\t\tWould You Like To Enter Another Ingredient (y/n)? ");
		YESNOCHOICE(choice);
	} while (choice != 'N');
	choice = '\0';
	do {
		printf("\t\tAdd An Instruction: ");
		readUserInputIntoRecipe(newRecipe->recipeInstructions[newRecipe->numberOfInstructions]);
		newRecipe->numberOfInstructions += 1;
		clearScreen();
		printFullRecipe(newRecipe);
		printf("\t\tWould You Like To Add Another Step (y/n)? ");
		YESNOCHOICE(choice);
	} while (choice != 'N');
	choice = '\0';
	printf("\t\tWould You Like To Add A Recipe Note (y/n)? ");
	YESNOCHOICE(choice);
	while (choice == 'Y'){
		readUserInputIntoRecipe(newRecipe->recipeNotes[newRecipe->numberOfNotes]);
		newRecipe->numberOfNotes += 1;
		clearScreen();
		printFullRecipe(newRecipe);
		printf("\t\tWould You Like To Add Another Note (y/n)? ");
		YESNOCHOICE(choice);
	}
	printFullRecipe(newRecipe);
	

	//function to move recipe into it's slot in the recipe linked list
	
	
	return recipeHeadPointer;
}