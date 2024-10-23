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
		puts("\n\n\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t      -CONVERT RECIPE- \t\t\t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		puts("\n\t\tMenu Options:\n");
	
		puts("\t\t(1) Convert New Recipe\n\t\t(2) Modify Recipe\n\t\t"
			 "(3) See Recipes By Type\n\t\t(4) Save Recipe As PDF\n\t\t"
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
	char choice = '\0';
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	clearScreen();
	puts("\n\n\t\t*********************************************************************************");
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
		strcpy(newRecipe->recipeName, buffer);
		clearScreen();
		printRecipeName(newRecipe);
		printf("\n\n\t\tIs The Above Correct (y/n)? ");
		YESNOCHOICE(choice);
	} while (choice != 'Y');
	strcpy(newRecipe->recipeName, buffer);
	clearScreen();
	printRecipeName(newRecipe);
	clearScreen();
	printRecipeName(newRecipe);
	printRecipeIngredients(newRecipe);
	choice = '\0';
	do {
		addNewIngredient(newRecipe, ingredientHead);
		clearScreen();
		printRecipeName(newRecipe);
		printRecipeIngredients(newRecipe);
		printf("\n\n\n\t\tWould You Like To Enter Another Ingredient (y/n)? ");
		YESNOCHOICE(choice);
	} while (choice != 'N');
	choice = '\0';
	clearScreen();
	printRecipeName(newRecipe);
	printRecipeIngredients(newRecipe);
	do {
		addNewInstruction(newRecipe);
		clearScreen();
		printRecipeName(newRecipe);
		printRecipeIngredients(newRecipe);
		if (newRecipe->numberOfInstructions > 0)
			printRecipeInstructions(newRecipe);
		printf("\n\n\t\tWould You Like To Add Another Step (y/n)? ");
		YESNOCHOICE(choice);
	} while (choice != 'N');
	choice = '\0';
	printf("\n\n\t\tWould You Like To Add A Recipe NOTE (y/n)? ");
	YESNOCHOICE(choice);
	if (choice == 'Y'){
		clearScreen();
		printRecipeName(newRecipe);
		printRecipeIngredients(newRecipe);
		printRecipeInstructions(newRecipe);
	}
	while (choice == 'Y'){
		addNewNote(newRecipe);
		clearScreen();
		printRecipeName(newRecipe);
		printRecipeIngredients(newRecipe);
		printRecipeInstructions(newRecipe);
		printRecipeNotes(newRecipe);
		printf("\n\n\t\tWould You Like To Add Another Note (y/n)? ");
		YESNOCHOICE(choice);
	}
	setRecipeType(newRecipe);
	editRecipeMenu(newRecipe, ingredientHead);
	
	//function to place recipe into it's slot in the recipe linked list
	return recipeHeadPointer;
}

/************************************************************************************************************
* 																											*
*				menu for editing an already filled in recipeStruct 											*
*																											*
*************************************************************************************************************/
void editRecipeMenu(struct recipeStruct *recipe, struct ingredientType *ingredientHead){
	char menu = '\0';
	do {
		menu = '\0';
		clearScreen();
		printFullRecipe(recipe);
		puts("\n\n\t\tEdit Recipe Menu Options:");
		puts("\n\t\t(1) Edit Recipe Name\n\t\t(2) Edit Ingredients\n\t\t(3) Edit Instructions");
		puts("\t\t(4) Edit Notes\t\t\t(S) Save and Exit");
		printf("\n\n\t\tEnter Selection: ");
		do {
  	      menu = toupper(getchar());
    	    if (menu == '\n'){
   	     		printf("\t\tInvalid Selection: ");
           		continue;
        	}
        	while (getchar() != '\n');
			if (strchr("1234S", menu) == NULL)
				printf("\t\tInvalid Selection: ");
		} while (strchr("1234S", menu) == NULL);
		switch (menu){
			case '1':		modifyRecipeName(recipe);
							break;
			case '2':		editRecipeIngredientsMenu(recipe, ingredientHead);
							break;
			case '3':		editRecipeInstructionsMenu(recipe);
							break;
			case '4':		editRecipeNotesMenu(recipe);
							break;
			case 'S':		return;
			default:		break;
		}
	} while (menu != 'S');
}

/************************************************************************************************************
* 																											*
*				menu for modifying a recipeStruct's ingredients 											*
*																											*
*************************************************************************************************************/
void editRecipeIngredientsMenu(struct recipeStruct *recipe, struct ingredientType *ingredientHead){
	char menu = '\0';
	do {
		menu = '\0';
		clearScreen();
		printRecipeName(recipe);
		printRecipeIngredients(recipe);
		puts("\n\n\t\tModify Ingredient Menu Options: ");
		puts("\n\t\t(1) Add Another Ingredient\n\t\t(2) Modify Ingredient's Amount");
		puts("\t\t(3) Change Ingredient's Order\n\t\t(4) Delete Ingredient\n\n\t\t(B) Back To Edit Recipe Menu");
		printf("\n\n\t\tEnter Selection: ");
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
			case '1':		addNewIngredient(recipe, ingredientHead);
							break;
			case '2':		modifyIngredientAmount(recipe, ingredientHead);
							break;
			case '3':		modifyIngredientOrder(recipe);
							break;
			case '4':		deleteIngredientFromRecipe(recipe);
							break;
			case 'B':		return;
			default:		break;
		}
	} while (menu != 'B');
}

/************************************************************************************************************
* 																											*
*				menu for modifying a recipeStruct's instructions 											*
*																											*
*************************************************************************************************************/
void editRecipeInstructionsMenu(struct recipeStruct *recipe){
	char menu = '\0';
	do {
		menu = '\0';
		clearScreen();
		printRecipeName(recipe);
		printRecipeIngredients(recipe);
		printRecipeInstructions(recipe);
		puts("\n\n\t\tModify Instructions Menu Options: ");
		puts("\n\t\t(1) Add Another Instruction\n\t\t(2) Modify Instruction\n\t\t(3) Change Instructions Order\n\t\t(4) Delete Instruction\n\n\t\t(B) Back To Edit Recipe Menu");
		printf("\n\n\t\tEnter Selection: ");
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
			case '1':		addNewInstruction(recipe);
							break;
			case '2':		modifyInstruction(recipe);
							break;
			case '3':		modifyInstructionOrder(recipe);
							break;
			case '4':		deleteInstructionFromRecipe(recipe);
							break;
			case 'B':		return;
			default:		break;
		}
	} while (menu != 'B');
}

/************************************************************************************************************
* 																											*
*				menu for modifying a recipeStruct's notes		 											*
*																											*
*************************************************************************************************************/
void editRecipeNotesMenu(struct recipeStruct *recipe){
char menu = '\0';
	do {
		menu = '\0';
		clearScreen();
		printRecipeName(recipe);
		printRecipeIngredients(recipe);
		printRecipeInstructions(recipe);
		printRecipeNotes(recipe);
		puts("\n\n\t\tModify Note Menu Options: ");
		puts("\n\t\t(1) Add Another Note\n\t\t(2) Modify Note\n\t\t(3) Change Notes Order\n\t\t(4) Delete Note\n\n\t\t(B) Back To Edit Recipe Menu");
		printf("\n\n\t\tEnter Selection: ");
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
			case '1':		addNewNote(recipe);
							break;
			case '2':		modifyNote(recipe);
							break;
			case '3':		modifyNoteOrder(recipe);
							break;
			case '4':		deleteNoteFromRecipe(recipe);
							break;
			case 'B':		return;
			default:		break;
		}
	} while (menu != 'B');
}