#include <stdio.h>
#include <ctype.h>
#include "recipeMenus.h"
#include "recipeConversions.h"
#include "recipeLinkedList.h"
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"
#include "recipePrintFunctions.h"


/************************************************************************************************************
* 																											*
*				menu function for all recipe functions														*
*				returns a pointer to the recipeStruct linked list head										*
*																											*
*************************************************************************************************************/
struct recipeStruct *recipeMenus(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead){
	char menu = '\0';
	struct recipeStruct *recipeHeadPointer = recipeHead;
	clearScreen();
	do {
		clearScreen();
		puts("\n\n\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t      -CONVERT RECIPE- \t\t\t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		puts("\n\n\t\tMenu Options:\n");
	
		puts("\t\t(1) Convert New Recipe\n\t\t(2) Modify Existing Recipe\n\n\t\t(B) Back");
		printf("\n\t\tEnter Selection: ");
		do {
        	menu = toupper(getchar());
        	if (menu == '\n'){
            	printf("\t\tInvalid Selection: ");
            	continue;
        	}
        	while (getchar() != '\n');
			if (strchr("12B", menu) == NULL)
				printf("\t\tInvalid Selection: ");
		} while (strchr("12B", menu) == NULL);
		switch (menu){
			case '1':	recipeHeadPointer = convertNewRecipe(recipeHeadPointer, ingredientHead);
						break;
			case '2':	recipeHeadPointer = modifyExistingRecipeMenu(recipeHeadPointer, ingredientHead);
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
*				menu for editing an already filled in recipeStruct 											*
*				returns a pointer to the recipeStruct linked list head in case of delete recipe				*
*																											*
*************************************************************************************************************/
struct recipeStruct *editRecipeMenu(struct recipeStruct *recipe, struct recipeStruct *recipeHead, struct ingredientType *ingredientHead){
	char menu = '\0';
	struct recipeStruct *recipeHeadPointer = recipeHead;
	do {
		menu = '\0';
		clearScreen();
		printFullRecipe(recipe);
		puts("\n\n\t\tEdit Recipe Menu Options:");
		puts("\n\t\t(1) Edit Recipe Name\t\t\t(D) DELETE RECIPE\n\t\t(2) Edit Ingredients\n\t\t(3) Edit Instructions");
		puts("\t\t(4) Edit Notes\t\t\t\t(P) Print Recipe To PDF\n\t\t(5) Edit Recipe Type\t\t\t(S) Save and Exit");
		printf("\n\n\t\tEnter Selection: ");
		do {
  	      menu = toupper(getchar());
    	    if (menu == '\n'){
   	     		printf("\t\tInvalid Selection: ");
           		continue;
        	}
        	while (getchar() != '\n');
			if (strchr("12345SPD", menu) == NULL)
				printf("\t\tInvalid Selection: ");
		} while (strchr("12345SPD", menu) == NULL);
		switch (menu){
			case '1':		recipeHeadPointer = modifyRecipeName(recipeHeadPointer, recipe);
							break;
			case '2':		editRecipeIngredientsMenu(recipe, ingredientHead);
							break;
			case '3':		editRecipeInstructionsMenu(recipe);
							break;
			case '4':		editRecipeNotesMenu(recipe);
							break;
			case '5':		setRecipeType(recipe);
							break;
			case 'D':		recipeHeadPointer = deleteFullRecipeNode(recipeHeadPointer, recipe);
							break;
			case 'P':		printRecipeToPDF(recipe);
							break;
			case 'S':		dumpRecipesFromLinkedList(recipeHeadPointer);
							return recipeHeadPointer;
			default:		break;
		}
	} while ((menu != 'S') && (menu != 'D'));
	return recipeHeadPointer;
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
		puts("\n\t\t(1) Add Another Measured Ingredient\n\t\t(2) Add Another Non-Measured Ingredient\n\t\t(3) Modify An Ingredient's Amount");
		puts("\t\t(4) Change The Ingredients' Order\n\t\t(5) Delete An Ingredient\n\n\t\t(B) Back To Edit Recipe Menu");
		printf("\n\n\t\tEnter Selection: ");
		do {
			menu = toupper(getchar());
				if (menu == '\n'){
					printf("\t\tInvalid Selection: ");
					continue;
			}
			while (getchar() != '\n');
			if (strchr("12345B", menu) == NULL)
				printf("\t\tInvalid Selection: ");
		} while (strchr("12345B", menu) == NULL);
		switch (menu){
			case '1':		addNewIngredient(recipe, ingredientHead);
							break;
			case '2':		addNewNonMeasuredIngredient(recipe);
							break;
			case '3':		modifyIngredientAmount(recipe, ingredientHead);
							break;
			case '4':		modifyIngredientOrder(recipe);
							break;
			case '5':		deleteIngredientFromRecipe(recipe);
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

/************************************************************************************************************
* 																											*
*				menu for modifying or deleting an existing recipe in the recipeStruct linked list			*
*				returns a pointer to the recipeStruct linked list head in case of delete recipe				*
*																											*
*************************************************************************************************************/
struct recipeStruct *modifyExistingRecipeMenu(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead){
	struct recipeStruct *foundRecipe = NULL;
	struct recipeStruct *recipeHeadPointer = recipeHead;
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	clearScreen();
	puts("\n\n\t\t*********************************************************************************");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*\t\t\t      -MODIFY RECIPE- \t\t\t\t\t*");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*********************************************************************************");
	printf("\n\t\tEnter Recipe Name: ");
	readUserInputIntoBuffer(buffer);
	foundRecipe = findRecipe(recipeHeadPointer, buffer);
	if (foundRecipe)
			recipeHeadPointer = editRecipeMenu(foundRecipe, recipeHeadPointer, ingredientHead);
	return recipeHeadPointer;
}

/************************************************************************************************************
* 																											*
*				menu function for printing all recipes, printing by type, or find recipe to print			*
*				returns a pointer to the recipeStruct linked list head in case of delete recipe				*
*																											*
*************************************************************************************************************/
struct recipeStruct *printSavedRecipeMenus(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead){
	char menu = '\0';
	struct recipeStruct *recipeHeadPointer = recipeHead;
	char recipeBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	clearScreen();
	struct recipeStruct *foundRecipe = NULL;
	do {
		clearScreen();
		puts("\n\n\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t      -PRINT SAVED RECIPES- \t\t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		puts("\n\n\t\tMenu Options:\n");
	
		puts("\t\t(1) Find Recipe By Name\n\t\t(2) See All Recipes\n\t\t(3) See Recipes By Type\n\n\t\t"
			 "(B) Back");
		printf("\n\t\tEnter Selection: ");
		do {
        	menu = toupper(getchar());
        	if (menu == '\n'){
            	printf("\t\tInvalid Selection: ");
            	continue;
        	}
        	while (getchar() != '\n');
			if (strchr("123B", menu) == NULL)
				printf("\t\tInvalid Selection: ");
		} while (strchr("123B", menu) == NULL);
		switch (menu){
			case '1':	printf("\n\n\t\tEnter Recipe Name: ");
						readUserInputIntoBuffer(recipeBuffer);
						foundRecipe = findRecipe(recipeHead, recipeBuffer);
						if (foundRecipe)
							recipeHeadPointer = printFullRecipeWithPDFOption(foundRecipe, recipeHead, ingredientHead);
						break;
			case '2':	recipeHeadPointer = printAllRecipeNames(recipeHead, ingredientHead);
						break;
			case '3':	recipeHeadPointer = printRecipeByType(recipeHead, ingredientHead);
						break;
			case 'B':	return recipeHeadPointer;
			default:	clearScreen();
						printf("\n\t\tInvalid Selection, Try Again\n");
		}
	} while (menu != 'B');
	return recipeHeadPointer;
}
