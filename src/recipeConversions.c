#include <stdio.h>
#include <ctype.h>
#include "recipeConversions.h"
#include "recipeLinkedList.h"
#include "recipeMenus.h"
#include "ingredientItemLinkedList.h"
#include "ingredientConversions.h"

/*
x	Function to add new recipe
x	Function to add new ingredient
x	Function to add new note
x	Function to add new direction
x	Function to remove each (ingredient, note, direction)
x	Function to modify each (ingredient, note, direction, order of (ingredient, note, direction))
x	Function to display recipe in current state
8	Function to pretty print recipe to pdf
x	Function to store recipes in txt files
x	Function to retrieve recipes from txt files
11	Function to delete recipe
12	Function to search for recipe
13	Function to free all recipes calloc()ed on quit 
*/

/********************************************************************************************************************
* 																													*
*				menu for adding new recipe functions, returns pointer to newly added recipe							*
*																													*
*********************************************************************************************************************/
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
	recipeHeadPointer = editRecipeMenu(newRecipe, recipeHeadPointer, ingredientHead);
	//place recipe in linked-list alphabetically
	recipeHeadPointer = placeRecipeStructNode(recipeHeadPointer, newRecipe);
	//dump the list into it's .txt file now that a new recipe was added
	dumpRecipesFromLinkedList(recipeHeadPointer);
	//return pointer to head of recipe linked list with new recipe 
	return recipeHeadPointer;
}

/********************************************************************************************************************
* 																													*
*	  			add new ingredientStruct into newRecipe struct. increases numberOfIngredients on success			*
*																													*
*********************************************************************************************************************/
void addNewIngredient(struct recipeStruct *currentRecipe, struct ingredientType *head){
	struct ingredientItem *foundNewIngredient = NULL;
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	char cupsInputAmountBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	printf("\n\n\n\t\tWhat INGREDIENT Would You Like To Add? : ");
	readUserInputIntoBuffer(buffer);
	if ((foundNewIngredient = findIngredientItemNode(head, buffer, NULL)) == NULL){
		printf("\n\n\t\tIngredient Not Found");
		return;
	} else {
		strcpy(currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientName, foundNewIngredient->ingredientName);
		currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams = cupsToGrams(cupsInputAmountBuffer, foundNewIngredient);
		strcpy(currentRecipe->ingredients[currentRecipe->numberOfIngredients].userCupsInput, cupsInputAmountBuffer);
	}
	currentRecipe->numberOfIngredients += 1;
}

/********************************************************************************************************************
* 																													*
*	  			add new instruction into recipeStruct. increases numberOfInstruction on success						*
*																													*
*********************************************************************************************************************/
void addNewInstruction(struct recipeStruct *currentRecipe){
	printf("\n\n\t\tAdd An INSTRUCTION:\n\n\t\t(%i) ", currentRecipe->numberOfInstructions + 1);
	readUserInputIntoRecipe(currentRecipe->recipeInstructions[currentRecipe->numberOfInstructions]);
	currentRecipe->numberOfInstructions += 1;
}

/********************************************************************************************************************
* 																													*
*	  			add new note into recipeStruct. increases numberOfNotes on success									*
*																													*
*********************************************************************************************************************/
void addNewNote(struct recipeStruct *currentRecipe){
	printf("\n\n\t\tAdd a NOTE:\n\n\t\t(%i) ", currentRecipe->numberOfNotes +1);
	readUserInputIntoRecipe(currentRecipe->recipeNotes[currentRecipe->numberOfNotes]);
	currentRecipe->numberOfNotes += 1;
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
	puts("\n\n\t\t(1) APPETIZER\t\t(2) BAKED GOOD\t\t(3) BREAKFAST\t\t(4) DESSERT\n\n\t\t(5) LUNCH\t\t(6) ENTREE\t\t(7) SIDE DISH\t\t(8) SNACK\n\n\t\t(9)SOUP");
	printf("\n\n\t\tEnter Number(#) Of Food Type: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > 9)
			printf("\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > 9);
	currentRecipe->recipeType = choice - 1;
}

/********************************************************************************************************************
* 																													*
*	  			used to fill in a recipeDirection or recipeNote field of a recipeStruct								*
*																													*
*********************************************************************************************************************/
void readUserInputIntoRecipe(char directionsBuffer[MAX_INGREDIENT_TEXT]){
	char *temp = directionsBuffer;
	char ch = '\0';
	int counter = 0;
	int lineCounter = 0;
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
		if (((*(temp+counter-1) == ' ') && (*(temp+counter-2) == '.')) || ((*(temp+counter-1) == ' ') && (*(temp+counter-2) == '?')) || ((*(temp+counter-1) == ' ') && (*(temp+counter-2) == '!')))
			ch = toupper(ch);
		//capitalize I when it refers to self
		if ((((ch == ' ') && (*(temp+counter-1) == 'i')) || ((ch == 39) && (*(temp+counter-1) == 'i'))) && ((*(temp+counter-2) == ' ') || (*(temp+counter-2) == '\t') || (*(temp+counter-2) == '\n')))
			*(temp+counter-1) = 'I';
		*(temp+counter) = ch;
		lineCounter++;
		if (*(temp+counter) == ' ' && lineCounter > 68){
			*(temp+counter) = '\n';
			counter++;
			*(temp+counter) = '\t';
			counter++;
			*(temp+counter) = '\t';
			lineCounter = 0;
		}
		counter++;
	}
	if (*(temp+counter) == ' ')
		*(temp+counter) = '\0';  
}

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
	puts("\n\n\t\t\tINGREDIENTS:\n");
	int i = 0;
	for (; i < recipe->numberOfIngredients; i++)
		printf("\t\t%d)  %7.2f grams of %s (%s)\n", i + 1, recipe->ingredients[i].ingredientGrams, recipe->ingredients[i].ingredientName, recipe->ingredients[i].userCupsInput);
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
*	  			modifies the recipe's name in a recipeStruct														*
*																													*
*********************************************************************************************************************/
void modifyRecipeName(struct recipeStruct *recipe){
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	char choice = '\0';
	printRecipeName(recipe);
	do {
		printf("\n\n\t\tEnter Recipe's Modified Name: ");
		memset(buffer, 0, INGREDIENT_BUFFER_LEN);
		readUserInputIntoBuffer(buffer);
		printf("\n\n\t\t\t%s\n\n\n\t\tIs This Correct (y/n)? ", buffer);
		YESNOCHOICE(choice);
	} while (choice != 'Y');
	strcpy(recipe->recipeName, buffer);
}

/********************************************************************************************************************
* 																													*
*	  			modifies the amount of an ingredient in a recipeStruct's ingredient's array							*
*																													*
*********************************************************************************************************************/
void modifyIngredientAmount(struct recipeStruct *recipe, struct ingredientType *ingredientHead){
	int menu = 0;
	char choice = '\0';
	struct ingredientItem *foundNewIngredient = NULL;
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	char cupsInputAmountBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	printf("\n\n\t\tEnter Ingredient Number Whose Amount You Wish To Modify: ");
	do {
		menu = getNumericChoice();
		if (menu < 1 || menu > recipe->numberOfIngredients)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (menu < 1 || menu > recipe->numberOfIngredients);
	strcpy(buffer, recipe->ingredients[menu - 1].ingredientName);
	if ((foundNewIngredient = findIngredientItemNode(ingredientHead, buffer, NULL)) == NULL){
		printf("\n\n\t\tIngredient Not Found");
		return;
	} else {
		do {
			recipe->ingredients[menu - 1].ingredientGrams = cupsToGrams(cupsInputAmountBuffer, foundNewIngredient);
			strcpy(recipe->ingredients[menu - 1].userCupsInput, cupsInputAmountBuffer);
			printf("\n\n\t\t  %7.2f grams of %s (%s)\n", recipe->ingredients[menu - 1].ingredientGrams, recipe->ingredients[menu - 1].ingredientName, recipe->ingredients[menu - 1].userCupsInput);
			printf("\n\n\t\tIs This Correct (y/n)? ");
			YESNOCHOICE(choice);
		} while (choice != 'Y');
	}
}

/********************************************************************************************************************
* 																													*
*	  			reorders the ingredients in a recipeStruct's ingredient's array										*
*																													*
*********************************************************************************************************************/
void modifyIngredientOrder(struct recipeStruct *recipe){
	int choice = 0;
	int newChoice = 0;
	struct ingredientStruct ingredientToMove[1];
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	printf("\n\n\t\tEnter The Ingredient Number You You Wish To Reorder: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > recipe->numberOfIngredients)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > recipe->numberOfIngredients);
	ingredientToMove[0] = recipe->ingredients[choice - 1];
	printf("\n\n\t\tEnter The Ingredient's New Order Number: ");
	do {
		newChoice = getNumericChoice();
		if (newChoice < 1 || newChoice > recipe->numberOfIngredients)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (newChoice < 1 || newChoice > recipe->numberOfIngredients);
	if (newChoice > choice){
		do {
			recipe->ingredients[choice - 1] = recipe->ingredients[choice];
			choice++;
		} while (choice < newChoice);
		recipe->ingredients[newChoice - 1] = ingredientToMove[0];
	} else if (newChoice < choice){
		do {
			recipe->ingredients[choice - 1] = recipe->ingredients[choice - 2];
			choice--;
		} while (choice > newChoice);
		recipe->ingredients[newChoice - 1] = ingredientToMove[0];
	}
}

/********************************************************************************************************************
* 																													*
*	  			deletes an ingredients from a recipeStruct's ingredients array										*
*																													*
*********************************************************************************************************************/
void deleteIngredientFromRecipe(struct recipeStruct *recipe){
	int choice = 0;
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	printf("\n\n\t\tEnter The Ingredient Number You You Wish To DELETE: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > recipe->numberOfIngredients)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > recipe->numberOfIngredients);
	do {
		recipe->ingredients[choice - 1] = recipe->ingredients[choice];
		choice++;
	} while (choice < recipe->numberOfIngredients);
	memset(recipe->ingredients[recipe->numberOfIngredients].ingredientName, 0, INGREDIENT_BUFFER_LEN);
	memset(recipe->ingredients[recipe->numberOfIngredients].userCupsInput, 0, INGREDIENT_BUFFER_LEN);
	recipe->ingredients[recipe->numberOfIngredients].ingredientGrams = 0.0;
	recipe->numberOfIngredients -= 1;
}

/********************************************************************************************************************
* 																													*
*	  			modifies an instruction in a recipeStruct's instructions array										*
*																													*
*********************************************************************************************************************/
void modifyInstruction(struct recipeStruct *recipe){
	int choice = 0;
	char choice2 = '\0';
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	printRecipeInstructions(recipe);
	printf("\n\n\t\tEnter Number Of Instruction You Wish To Modify: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > recipe->numberOfInstructions)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > recipe->numberOfInstructions);
	printf("\n\n\t\t%s\n\n\t\tEnter New Instruction: ", recipe->recipeInstructions[choice - 1]);
	do {
		memset(buffer, 0, INGREDIENT_BUFFER_LEN);
		readUserInputIntoRecipe(buffer);
		printf("\n\n\t\t%s\n\n\t\tIs This Correct (y/n)? ", buffer);
		YESNOCHOICE(choice2);
	} while (choice2 != 'Y');
	memset(recipe->recipeInstructions[choice - 1], 0, MAX_INGREDIENT_TEXT);
	strcpy(recipe->recipeInstructions[choice - 1], buffer);
}

/********************************************************************************************************************
* 																													*
*	  			reorders the instructions in a recipeStruct's instructions array									*
*																													*
*********************************************************************************************************************/
void modifyInstructionOrder(struct recipeStruct *recipe){
	int choice = 0;
	int newChoice = 0;
	char instructionToMove[MAX_INGREDIENT_TEXT] = {'\0'};
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	printRecipeInstructions(recipe);
	printf("\n\n\t\tEnter The Instruction Number You You Wish To Reorder: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > recipe->numberOfInstructions)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > recipe->numberOfInstructions);
	strcpy(instructionToMove, recipe->recipeInstructions[choice - 1]);
	printf("\n\n\t\tEnter The Instruction's New Order Number: ");
	do {
		newChoice = getNumericChoice();
		if (newChoice < 1 || newChoice > recipe->numberOfInstructions)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (newChoice < 1 || newChoice > recipe->numberOfInstructions);
	if (newChoice > choice){
		do {
			strcpy(recipe->recipeInstructions[choice - 1], recipe->recipeInstructions[choice]);
			choice++;
		} while (choice < newChoice);
		strcpy(recipe->recipeInstructions[choice - 1], instructionToMove);
	} else if (newChoice < choice){
		do {
			strcpy(recipe->recipeInstructions[choice - 1], recipe->recipeInstructions[choice - 2]);
			choice--;
		} while (choice > newChoice);
		strcpy(recipe->recipeInstructions[choice - 1], instructionToMove);
	}
}

/********************************************************************************************************************
* 																													*
*	  			deletes an instruction from a recipeStruct's instructions array										*
*																													*
*********************************************************************************************************************/
void deleteInstructionFromRecipe(struct recipeStruct *recipe){
	int choice = 0;
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	printRecipeInstructions(recipe);
	printf("\n\n\t\tEnter The Instruction Number You You Wish To DELETE: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > recipe->numberOfInstructions)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > recipe->numberOfInstructions);
	do {
		strcpy(recipe->recipeInstructions[choice - 1], recipe->recipeInstructions[choice]);
		choice++;
	} while (choice < recipe->numberOfInstructions);
	memset(recipe->recipeInstructions[choice], 0, MAX_INGREDIENT_TEXT);
	recipe->numberOfInstructions -= 1;
}

/********************************************************************************************************************
* 																													*
*	  			modifies an instruction in a recipeStruct's notes array												*
*																													*
*********************************************************************************************************************/
void modifyNote(struct recipeStruct *recipe){
	int choice = 0;
	char choice2 = '\0';
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	printRecipeInstructions(recipe);
	printRecipeNotes(recipe);
	printf("\n\n\t\tEnter Number Of Note You Wish To Modify: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > recipe->numberOfNotes)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > recipe->numberOfNotes);
	printf("\n\n\t\t%s\n\n\t\tEnter New Note: ", recipe->recipeNotes[choice - 1]);
	do {
		memset(buffer, 0, INGREDIENT_BUFFER_LEN);
		readUserInputIntoRecipe(buffer);
		printf("\n\n\t\t%s\n\n\t\tIs This Correct (y/n)? ", buffer);
		YESNOCHOICE(choice2);
	} while (choice2 != 'Y');
	memset(recipe->recipeNotes[choice - 1], 0, MAX_INGREDIENT_TEXT);
	strcpy(recipe->recipeNotes[choice - 1], buffer);
}

/********************************************************************************************************************
* 																													*
*	  			reorders the notes in a recipeStruct's notes array													*
*																													*
*********************************************************************************************************************/
void modifyNoteOrder(struct recipeStruct *recipe){
	int choice = 0;
	int newChoice = 0;
	char noteToMove[MAX_INGREDIENT_TEXT] = {'\0'};
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	printRecipeInstructions(recipe);
	printRecipeNotes(recipe);
	printf("\n\n\t\tEnter The Note Number You You Wish To Reorder: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > recipe->numberOfInstructions)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > recipe->numberOfNotes);
	strcpy(noteToMove, recipe->recipeNotes[choice - 1]);
	printf("\n\n\t\tEnter The Note's New Order Number: ");
	do {
		newChoice = getNumericChoice();
		if (newChoice < 1 || newChoice > recipe->numberOfNotes)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (newChoice < 1 || newChoice > recipe->numberOfNotes);
	if (newChoice > choice){
		do {
			strcpy(recipe->recipeNotes[choice - 1], recipe->recipeNotes[choice]);
			choice++;
		} while (choice < newChoice);
		strcpy(recipe->recipeNotes[choice - 1], noteToMove);
	} else if (newChoice < choice){
		do {
			strcpy(recipe->recipeNotes[choice - 1], recipe->recipeNotes[choice - 2]);
			choice--;
		} while (choice > newChoice);
		strcpy(recipe->recipeNotes[choice - 1], noteToMove);
	}
}

/********************************************************************************************************************
* 																													*
*	  			deletes a note in a recipeStruct's notes array														*
*																													*
*********************************************************************************************************************/
void deleteNoteFromRecipe(struct recipeStruct *recipe){
	int choice = 0;
	clearScreen();
	printRecipeName(recipe);
	printRecipeIngredients(recipe);
	printRecipeInstructions(recipe);
	printRecipeNotes(recipe);
	printf("\n\n\t\tEnter The Note Number You You Wish To DELETE: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > recipe->numberOfNotes)
			printf("\n\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > recipe->numberOfNotes);
	do {
		strcpy(recipe->recipeNotes[choice - 1], recipe->recipeNotes[choice]);
		choice++;
	} while (choice < recipe->numberOfNotes);
	memset(recipe->recipeNotes[choice], 0, MAX_INGREDIENT_TEXT);
	recipe->numberOfNotes -= 1;
}