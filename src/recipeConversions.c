#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include "recipeConversions.h"
#include "recipeLinkedList.h"
#include "recipeMenus.h"
#include "ingredientItemLinkedList.h"
#include "ingredientConversions.h"
#include "recipeSystemCheck.h"
#include "recipePrintFunctions.h"
#include "pdfgen.h"

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
	//loop option for adding measured or non-measured ingredient
	int numericChoice = 0;
	do {
		choice = '\0';
		do {
			printf("\n\t\t(1) Add New Measured Ingredient\n\t\t(2) Add New Non-Measured Ingredient");
			if (newRecipe->numberOfIngredients == 0)
				printf("\n\n\t\tEnter Selection: ");
			if (newRecipe->numberOfIngredients > 0)
				printf("\n\t\t(3) Continue To Instructions\n\n\t\tEnter Selection: ");
			numericChoice = getNumericChoice();
			if (numericChoice != 1 && numericChoice != 2 && numericChoice != 3)
            	printf("\t\tInvalid Selection, Try Again");
		} while (numericChoice != 1 && numericChoice != 2 && numericChoice != 3);
		if (numericChoice == 1){
			do {
				addNewIngredient(newRecipe, ingredientHead);
				clearScreen();
				printRecipeName(newRecipe);
				printRecipeIngredients(newRecipe);
				printf("\n\n\n\t\tWould You Like To Enter Another Measured Ingredient (y/n)? ");
				YESNOCHOICE(choice);
			} while (choice != 'N');
		} else if (numericChoice == 2){
			do {
				addNewNonMeasuredIngredient(newRecipe);
				clearScreen();
				printRecipeName(newRecipe);
				printRecipeIngredients(newRecipe);
				printf("\n\n\n\t\tWould You Like To Enter Another Non-Measured, Non-Weighed Ingredient (y/n)? ");
				YESNOCHOICE(choice);
			} while (choice != 'N');
		}
	} while (numericChoice != 3);
	
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
	//place recipe in linked-list alphabetically
	struct recipeStruct *temp = placeRecipeStructNode(recipeHeadPointer, newRecipe);
	//if temp == NULL then the recipe was deleted b/c of conflicting name rather than renamed
	if (temp){
		recipeHeadPointer = temp;
		recipeHeadPointer = editRecipeMenu(newRecipe, recipeHeadPointer, ingredientHead);
	}
	//return pointer to head of recipe linked list with new recipe 
	return recipeHeadPointer;
}

/********************************************************************************************************************
* 																													*
*	  			add new ingredientStruct into currentRecipe struct. increases numberOfIngredients on success		*
*																													*
*********************************************************************************************************************/
void addNewIngredient(struct recipeStruct *currentRecipe, struct ingredientType *head){
	struct ingredientItem *foundNewIngredient = NULL;
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	char cupsInputAmountBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	int measurableIngredient = 0;
	char choice = '\0';
	printf("\n\n\n");
	do {
		memset(buffer, 0, sizeof(buffer));
		printf("\t\tWhat INGREDIENT Would You Like To Add? : ");
		readUserInputIntoBuffer(buffer);
		if ((foundNewIngredient = findIngredientItemNode(head, buffer, NULL)) == NULL){
			printf("\n\n\t\t%s\n\n\t\tIngredient Measurements Not Found. Add Ingredient By Weight (y/n)? ", buffer);
			YESNOCHOICE(choice);
		} else (measurableIngredient = 1, choice = 'Y');
	} while (choice != 'Y');
	if (measurableIngredient == 1){
		strcpy(currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientName, foundNewIngredient->ingredientName);
		currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams = cupsToGrams(cupsInputAmountBuffer, foundNewIngredient);
		if (currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams >= 100)
			currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams = round(currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams);
		strcpy(currentRecipe->ingredients[currentRecipe->numberOfIngredients].userCupsInput, cupsInputAmountBuffer);
	} else {
		strcpy(currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientName, buffer);
		currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams = weightToGrams(cupsInputAmountBuffer, currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientName);
		if (currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams >= 100)
			currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams = round(currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams);
		strcpy(currentRecipe->ingredients[currentRecipe->numberOfIngredients].userCupsInput, cupsInputAmountBuffer);
	}
	currentRecipe->numberOfIngredients += 1;
}

/********************************************************************************************************************
* 																													*
*	  			add a new unmeasured ingredient into an ingredientStruct in currentRecipe struct. 					*
*				increases numberOfIngredients on success															*
*																													*
*********************************************************************************************************************/
void addNewNonMeasuredIngredient(struct recipeStruct *currentRecipe){
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	char ingredientNotes[INGREDIENT_BUFFER_LEN] = {'\0'};
	char choice = '\0';
	printf("\n\n\n");
	do {
		memset(buffer, 0, sizeof(buffer));
		printf("\t\tWhat Non-Measured INGREDIENT Would You Like To Add? : ");
		readUserInputIntoBuffer(buffer);
		printf("\n\n\t\t%s\n\n\t\tIs This Correct (y/n)? ", buffer);
		YESNOCHOICE(choice);
	} while (choice != 'Y');
	strcpy(currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientName, buffer);
	printf("\n\n\t\tEnter The Number of %s In Your Recipe (Enter 0 To Leave Blank): ", buffer);
	float inputCheck = 0.0;
	char amountBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	do {
		readUserInputIntoBuffer(amountBuffer);
		inputCheck = getCups(amountBuffer);
		if (inputCheck == -1.0){
			printf("\n\n\t\tInvalid Entry, Please Enter The Number Of %s In Your Recipe: ", buffer);
			memset(amountBuffer, 0, sizeof(amountBuffer));
		}
	} while (inputCheck == -1.0);
	currentRecipe->ingredients[currentRecipe->numberOfIngredients].ingredientGrams = inputCheck;
	choice = '\0';
	do {
		memset(ingredientNotes, 0, sizeof(ingredientNotes));
		printf("\n\t\tEnter Notes For This Ingredient (Size, Weight, How To Prepare, etc, Or Hit Enter To Leave Empty): ");
		char ch = '\0';
		if ((ch = getchar()) == '\n'){
			break;
		} else
			ungetc(ch, stdin);
		int charCounter = readUserInputIntoBuffer(ingredientNotes);
		//safety for buffer overflow using readUserInputIntoRecipe as it has a longer input allowed than the buffer can take
		if (charCounter > INGREDIENT_BUFFER_LEN){
			char ch = '\0';
			while ((ch = getchar()) != '\n');
			printf("\n\t\tInput Too Long, Try Again: ");
			continue;
		}
		printf("\n\t\t%s\n\n\t\tIs This Correct (y/n)? ", ingredientNotes);
		YESNOCHOICE(choice);
	} while (choice != 'Y');
	strcpy(currentRecipe->ingredients[currentRecipe->numberOfIngredients].userCupsInput, ingredientNotes);
	currentRecipe->ingredients[currentRecipe->numberOfIngredients].nonWeighedIngredientFlag = 1;
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
	puts("\n\n\t\t(1) APPETIZER\t\t(2) BAKED GOOD\t\t(3) BREAKFAST\t\t(4) DESSERT\n\n\t\t(5) LUNCH\t\t(6) ENTREE\t\t(7) SIDE DISH\t\t(8) SNACK\n\n\t\t(9) SOUP");
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
*				returns the number of succesfull characters placed into the directionsBuffer						*
*																													*
********************************************************************************************************************/
int readUserInputIntoRecipe(char directionsBuffer[MAX_INGREDIENT_TEXT]){
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
		if (((ch == ' ') || (ch == '\t')) && (((*(temp+counter-1) == ' ')) || (*(temp+counter-1) == '\t')))
			continue;
		//capitalize first letter of new sentence
		if (((*(temp+counter-1) == ' ') && (*(temp+counter-2) == '.')) || ((*(temp+counter-1) == ' ') && (*(temp+counter-2) == '?')) || ((*(temp+counter-1) == ' ') && (*(temp+counter-2) == '!')) || ((*(temp+counter-1) == '\t') && (*(temp+counter-4) == '.')))
			ch = toupper(ch);
		//capitalize I when it refers to self
		if ((((ch == ' ') && (*(temp+counter-1) == 'i')) || ((ch == 39) && (*(temp+counter-1) == 'i'))) && ((*(temp+counter-2) == ' ') || (*(temp+counter-2) == '\t') || (*(temp+counter-2) == '\n')))
			*(temp+counter-1) = 'I';
		if (((ch == 'f') || (ch == 'c')) && (*(temp + counter - 1) == '*'))
			ch = toupper(ch);
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
	return counter;
}

/********************************************************************************************************************
* 																													*
*	  			modifies the recipe's name in a recipeStruct, returns a pointer to recipeStruct head				*
*				for when recipe name change moves position in linked list											*
*																													*
*********************************************************************************************************************/
struct recipeStruct *modifyRecipeName(struct recipeStruct *recipeHead, struct recipeStruct *recipe){
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	char choice = '\0';
	struct recipeStruct *prev = recipe->prev;
	struct recipeStruct *next = recipe->next;
	struct recipeStruct *head = recipeHead;
	printRecipeName(recipe);
	do {
		printf("\n\n\t\tEnter Recipe's Modified Name: ");
		memset(buffer, 0, INGREDIENT_BUFFER_LEN);
		readUserInputIntoBuffer(buffer);
		printf("\n\n\t\t\t%s\n\n\n\t\tIs This Correct (y/n)? ", buffer);
		YESNOCHOICE(choice);
	} while (choice != 'Y');
	strcpy(recipe->recipeName, buffer);
	//if it is still in the right place alphabetically:
	if (((prev && next) && ((strcmp(recipe->recipeName, prev->recipeName) > 0) && (strcmp(recipe->recipeName, next->recipeName) < 0)))
		|| ((!prev && next) && (strcmp(recipe->recipeName, next->recipeName) < 0)) || ((prev && !next) && (strcmp(recipe->recipeName, prev->recipeName) > 0))){
		return recipeHead;
	//if not and it is the first node: 
	} else {
		recipe->prev = NULL;
		recipe->next = NULL;
	 	if (!prev && next){
			next->prev = NULL;
			head = next;
		//if it is a middle node:
		} else if (prev && next){
			prev->next = next;
			next->prev = prev;
		//if it is the final node:
		} else if (prev && !next){
			prev->next = NULL;
		}
	}
	//check for NULL if name conflicted and recipe node was free'd instead of renamed
	struct recipeStruct *temp = placeRecipeStructNode(head, recipe);
	if (temp)
		head = temp;
	return head;
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
	//choice between if it's a measured or non-measured ingredient
	if (recipe->ingredients[menu - 1].nonWeighedIngredientFlag == 0){
		strcpy(buffer, recipe->ingredients[menu - 1].ingredientName);
		if ((foundNewIngredient = findIngredientItemNode(ingredientHead, buffer, NULL)) == NULL){
		do {
				recipe->ingredients[menu - 1].ingredientGrams = weightToGrams(cupsInputAmountBuffer, buffer);
				if (recipe->ingredients[menu - 1].ingredientGrams >= 100)
					recipe->ingredients[menu - 1].ingredientGrams = round(recipe->ingredients[menu - 1].ingredientGrams);
				strcpy(recipe->ingredients[menu - 1].userCupsInput, cupsInputAmountBuffer);
				printf("\n\n\t\t  %7.2f grams of %s (%s)\n", recipe->ingredients[menu - 1].ingredientGrams, recipe->ingredients[menu - 1].ingredientName, recipe->ingredients[menu - 1].userCupsInput);
				printf("\n\n\t\tIs This Correct (y/n)? ");
				YESNOCHOICE(choice);
			} while (choice != 'Y');
	//		printf("\n\n\t\tIngredient Not Found");
	//		return;
		} else {
			do {
				recipe->ingredients[menu - 1].ingredientGrams = cupsToGrams(cupsInputAmountBuffer, foundNewIngredient);
				strcpy(recipe->ingredients[menu - 1].userCupsInput, cupsInputAmountBuffer);
				if (recipe->ingredients[menu - 1].ingredientGrams >= 100)
					recipe->ingredients[menu - 1].ingredientGrams = round(recipe->ingredients[menu - 1].ingredientGrams);
				printf("\n\n\t\t  %7.2f grams of %s (%s)\n", recipe->ingredients[menu - 1].ingredientGrams, recipe->ingredients[menu - 1].ingredientName, recipe->ingredients[menu - 1].userCupsInput);
				printf("\n\n\t\tIs This Correct (y/n)? ");
				YESNOCHOICE(choice);
			} while (choice != 'Y');
		}
	} else {
		printf("\n\n\t\tEnter The Number of %s In Your Recipe: ", recipe->ingredients[menu - 1].ingredientName);
		float inputCheck = 0.0;
		char amountBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
		do {
			readUserInputIntoBuffer(amountBuffer);
			inputCheck = getCups(amountBuffer);
			if (inputCheck == -1.0){
				printf("\n\n\t\tInvalid Entry, Please Enter The Number Of %s In Your Recipe: ", recipe->ingredients[menu - 1].ingredientName);
				memset(amountBuffer, 0, sizeof(amountBuffer));
			} else
				recipe->ingredients[menu - 1].ingredientGrams = inputCheck;
		} while (inputCheck == -1.0);
		printf("\n\n\t\tModify Note For This Ingredient (y/n)? ");
		char choice = '\0';
		YESNOCHOICE(choice);
		if (choice == 'Y'){
			char ingredientNotes[INGREDIENT_BUFFER_LEN] = {'\0'};
			do {
				choice = '\0';
				memset(ingredientNotes, 0, sizeof(ingredientNotes));
				printf("\t\tEnter Notes For This Ingredient (Size, Weight, How To Prepare, etc): ");
				int charCounter = readUserInputIntoBuffer(ingredientNotes);
				//safety for buffer overflow using readUserInputIntoRecipe as it has a longer input allowed than the buffer can take
				if (charCounter > INGREDIENT_BUFFER_LEN){
					char ch = '\0';
					while ((ch = getchar()) != '\n')
						;
					printf("\n\t\tInput Too Long, Try Again: ");
					continue;
				}
				printf("\t\t%s\n\n\t\tIs This Correct (y/n)? ", ingredientNotes);
				YESNOCHOICE(choice);
			} while (choice == 'N');
			memset(recipe->ingredients[menu - 1].userCupsInput, 0, sizeof(recipe->ingredients[menu - 1].userCupsInput));
			strcpy(recipe->ingredients[menu - 1].userCupsInput, ingredientNotes);
		}
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
	char buffer[MAX_INGREDIENT_TEXT] = {'\0'};
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
	do {
		printf("\n\n\t\t%s\n\n\t\tEnter New Instruction: ", recipe->recipeInstructions[choice - 1]);
		memset(buffer, 0, MAX_INGREDIENT_TEXT);
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
	char buffer[MAX_INGREDIENT_TEXT] = {'\0'};
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
	do {
		printf("\n\n\t\t%s\n\n\t\tEnter New Note: ", recipe->recipeNotes[choice - 1]);
		memset(buffer, 0, MAX_INGREDIENT_TEXT);
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

/********************************************************************************************************************
* 																													*
*	  			accepts a recipeInstructions or recipeNotes formatted buffer and a buffer to store the PDF text		*
*				and returns the number of characters successfully copied into the PDF format buffer					*
*																													*
*********************************************************************************************************************/
int recipeBufferToPDFOutput (char *recipeToPDFBuffer, char *recipeNodeText){
	char *recipeToPDFBufferPointer = recipeToPDFBuffer;
	char *recipeNodeTextPointer = recipeNodeText;
	int recipeNodeBufferCounter = 0;
	int pdfBufferCounter = 0;
	while (*(recipeNodeTextPointer + recipeNodeBufferCounter) != '\0'){
		if ((*(recipeNodeTextPointer + recipeNodeBufferCounter) == '\t') || (*(recipeNodeTextPointer + recipeNodeBufferCounter) == '\n')){
			recipeNodeBufferCounter++;
			if ((*(recipeNodeTextPointer + (recipeNodeBufferCounter - 1)) == '\t') && (*(recipeNodeTextPointer + recipeNodeBufferCounter - 2) == '\t'))
				*(recipeToPDFBufferPointer + pdfBufferCounter++) = ' ';
		} else {
			*(recipeToPDFBufferPointer + pdfBufferCounter++) = *(recipeNodeTextPointer + recipeNodeBufferCounter++);
		}
	}
	return pdfBufferCounter;
}

/********************************************************************************************************************
* 																													*
*	  			saves a recipe to as a pdf document in a visually pleasing uniform style							*
*																													*
*********************************************************************************************************************/
void printRecipeToPDF(struct recipeStruct *recipeToPrint){
	FILE *fp = NULL;
	char openFileBuffer[PATH_MAX] = {'\0'};
	#ifdef _WIN32
		snprintf(openFileBuffer, sizeof(openFileBuffer), "%s\\recipePDFs\\%s.pdf", pathwayBuffer, recipeToPrint->recipeName);
	#else
		snprintf(openFileBuffer, sizeof(openFileBuffer), "%s/recipePDFs/%s.pdf", pathwayBuffer, recipeToPrint->recipeName);
	#endif
	if ((fp = fopen(openFileBuffer, "wb")) == NULL){
		printf("Unable to open %s file\n", openFileBuffer);
		return;
	}
	struct pdf_info info = {
        .creator = "Recipe Conversions",
        .producer = "PDFgen",
        .author = "Matthew Freedman",
        .subject = "Cups To Grams Conversions",
        .date = "Today"
    };
    strcpy(info.title, recipeToPrint->recipeName);
    //create my pdf pointer for pdfgen.h
	struct pdf_doc *pdf = pdf_create(PDF_LETTER_WIDTH, PDF_LETTER_HEIGHT, &info);
	//set the pdf's font to Helvetica
	pdf_set_font(pdf, "Helvetica");
	//add a new page to the PDF
	pdf_append_page(pdf);
	int linePointCounter = 0; //number to deduct from top line of page
	//add recipe name box at top and type at bottom of page
	printRecipeNameAndTypeToPDF(pdf, recipeToPrint, &linePointCounter);
	//add ingredients
	pdf_add_text(pdf, NULL, "        INGREDIENTS:", 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
	linePointCounter += (1.5 * V_FONT_POINTS);
	char ingredientBuffer[INGREDIENT_BUFFER_LEN * 2] = {'\0'};
	//lineCounter so you don't get page overflow
	int lineCounter = 0;
	int largestIngredientSize = 0;
	int largestIngredientSizeLeft = 0;
	int largestIngredientSizeRight = 0;
	int tempIngredientSize = 0;
	int largestNameCommentSize = 0;
	int tempNameCommentSize = 0;
	int nameCommentSizeOffset = 0;
	struct ingredientStruct *largestIngredientNamePtr = NULL;
	//check every ingredient's decimal place amount in the total grams to get the largest number of printed digits of every ingredients' grams size
	char ingredientGramsPrintBuffer[11] = {'\0'};
	if (recipeToPrint->numberOfIngredients > 6){
		int printHalf = 0;
		if (recipeToPrint->numberOfIngredients % 2 == 0)
			printHalf = (recipeToPrint->numberOfIngredients / 2);
		else
			printHalf = (recipeToPrint->numberOfIngredients / 2) + 1;
		for (int i = 0; i < recipeToPrint->numberOfIngredients; i++){
			memset(ingredientGramsPrintBuffer, 0, sizeof(ingredientGramsPrintBuffer));
			decimalPlaceCheck(recipeToPrint->ingredients[i].ingredientGrams, ingredientGramsPrintBuffer);
			tempIngredientSize = strlen(ingredientGramsPrintBuffer);
			if (i <= printHalf){
				if (tempIngredientSize > largestIngredientSizeLeft)
					largestIngredientSizeLeft = tempIngredientSize;
			} else {
				if (tempIngredientSize > largestIngredientSizeRight)
					largestIngredientSizeRight = tempIngredientSize;
			}
			tempNameCommentSize = (strlen(recipeToPrint->ingredients[i].ingredientName) + strlen(recipeToPrint->ingredients[i].userCupsInput));
			if (tempNameCommentSize > largestNameCommentSize){
				largestNameCommentSize = tempNameCommentSize;
				largestIngredientNamePtr = &recipeToPrint->ingredients[i];
			}
		}
		//check if the largestNameCommentSize came from a measured ingredient or not, then check it size and decrease font size if needed
		if ((largestIngredientNamePtr->nonWeighedIngredientFlag == 0 && largestNameCommentSize > 40) || (largestIngredientNamePtr->nonWeighedIngredientFlag == 1 && largestNameCommentSize > 49))
			nameCommentSizeOffset = 1;
		#undef V_FONT_POINTS
		#define V_FONT_POINTS 10
		//ingredientSizeOffset offset is to print all the ingredient names along the same vertical line regardless of the number of grams or individual items used of each ingredient
		int ingredientSizeOffsetLeft = (largestIngredientSizeLeft + 2) * H_FONT_POINTS; //+1.5 for the #) chars
		int ingredientSizeOffsetRight = (largestIngredientSizeRight + 2.5) * H_FONT_POINTS;
		for (int i = 0; i < printHalf; i++){
			memset(ingredientGramsPrintBuffer, 0, sizeof(ingredientGramsPrintBuffer));
			char ingredientGramsPrintBuffer[11] = {'\0'}; //11 is the max size you could find in the %7.2f buffer input plus a nul character at the end
			decimalPlaceCheck(recipeToPrint->ingredients[i].ingredientGrams, ingredientGramsPrintBuffer);
			snprintf(ingredientBuffer, 5, "%d)", i + 1);
			pdf_add_text(pdf, NULL, ingredientBuffer, V_FONT_POINTS - nameCommentSizeOffset, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
		//add the size in grams aligned right to the size of the largestIngredientSize buffer
			if (recipeToPrint->ingredients[i].ingredientGrams > 0)
				pdf_add_text_wrap(pdf, NULL, ingredientGramsPrintBuffer, V_FONT_POINTS - nameCommentSizeOffset, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, 0, PDF_BLACK, ingredientSizeOffsetLeft, PDF_ALIGN_RIGHT, NULL);
			memset(ingredientBuffer, 0, sizeof(ingredientBuffer));
		//print the ingredient w/ the () bracket info, if there is no info, print the recipe to buffer with out
			if (recipeToPrint->ingredients[i].nonWeighedIngredientFlag == 1){
				if (strlen(recipeToPrint->ingredients[i].userCupsInput) > 0)
					snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN * 2, "  %s (%s)", recipeToPrint->ingredients[i].ingredientName, recipeToPrint->ingredients[i].userCupsInput);
				else (snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN + 2, "  %s", recipeToPrint->ingredients[i].ingredientName));
			} else {
				if (strlen(recipeToPrint->ingredients[i].userCupsInput) > 0)
					snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN * 2, "  Grams Of %s (%s)", recipeToPrint->ingredients[i].ingredientName, recipeToPrint->ingredients[i].userCupsInput);
				else (snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN + 12, "  Grams Of %s", recipeToPrint->ingredients[i].ingredientName));
			}
			pdf_add_text(pdf, NULL, ingredientBuffer, V_FONT_POINTS - nameCommentSizeOffset, SIDE_MARGIN + ingredientSizeOffsetLeft, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
		
		//print the 2nd column
			if ((i + printHalf) < recipeToPrint->numberOfIngredients){
				memset(ingredientGramsPrintBuffer, 0, sizeof(ingredientGramsPrintBuffer));
				char ingredientGramsPrintBuffer[11] = {'\0'}; //11 is the max size you could find in the %7.2f buffer input plus a nul character at the end
				decimalPlaceCheck(recipeToPrint->ingredients[i + printHalf].ingredientGrams, ingredientGramsPrintBuffer);
				snprintf(ingredientBuffer, 5, "%d)", i + printHalf + 1);
				pdf_add_text(pdf, NULL, ingredientBuffer, V_FONT_POINTS - nameCommentSizeOffset, (TOTAL_HORIZONTAL_POINTS / 2), TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
		//add the size in grams aligned right to the size of the largestIngredientSize buffer
				if (recipeToPrint->ingredients[i + printHalf].ingredientGrams > 0)
					pdf_add_text_wrap(pdf, NULL, ingredientGramsPrintBuffer, V_FONT_POINTS - nameCommentSizeOffset, (TOTAL_HORIZONTAL_POINTS / 2), TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, 0, PDF_BLACK, ingredientSizeOffsetRight, PDF_ALIGN_RIGHT, NULL);
				memset(ingredientBuffer, 0, sizeof(ingredientBuffer));
		//print the ingredient w/ the () bracket info, if there is no info, print the recipe to buffer with out
				if (recipeToPrint->ingredients[i + printHalf].nonWeighedIngredientFlag == 1){
					if (strlen(recipeToPrint->ingredients[i + printHalf].userCupsInput) > 0)
						snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN * 2, "  %s (%s)", recipeToPrint->ingredients[i + printHalf].ingredientName, recipeToPrint->ingredients[i + printHalf].userCupsInput);
					else (snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN + 2, "  %s", recipeToPrint->ingredients[i + printHalf].ingredientName));
				} else {
					if (strlen(recipeToPrint->ingredients[i + printHalf].userCupsInput) > 0)
						snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN * 2, "  Grams Of %s (%s)", recipeToPrint->ingredients[i + printHalf].ingredientName, recipeToPrint->ingredients[i + printHalf].userCupsInput);
					else (snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN + 12, "  Grams Of %s", recipeToPrint->ingredients[i + printHalf].ingredientName));
				}
				pdf_add_text(pdf, NULL, ingredientBuffer, V_FONT_POINTS - nameCommentSizeOffset, (TOTAL_HORIZONTAL_POINTS / 2) + ingredientSizeOffsetRight, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
			}
			linePointCounter += 1.5 * V_FONT_POINTS;
			lineCounter++;
		}
		#undef V_FONT_POINTS
		#define V_FONT_POINTS 12
	} else {
		for (int i = 0; i < recipeToPrint->numberOfIngredients; i++){
		memset(ingredientGramsPrintBuffer, 0, sizeof(ingredientGramsPrintBuffer));
		decimalPlaceCheck(recipeToPrint->ingredients[i].ingredientGrams, ingredientGramsPrintBuffer);
		tempIngredientSize = strlen(ingredientGramsPrintBuffer);
		if (tempIngredientSize > largestIngredientSize)
			largestIngredientSize = tempIngredientSize;
		}
	//ingredientSizeOffset offset is to print all the ingredient names along the same vertical line regardless of the number of grams or individual items used of each ingredient
		int ingredientSizeOffset = (largestIngredientSize + 1.5) * H_FONT_POINTS; //+1 for the #) chars
		for (int i = 0; i < recipeToPrint->numberOfIngredients; i++){
			memset(ingredientGramsPrintBuffer, 0, sizeof(ingredientGramsPrintBuffer));
			char ingredientGramsPrintBuffer[11] = {'\0'}; //11 is the max size you could find in the %7.2f buffer input plus a nul character at the end
			decimalPlaceCheck(recipeToPrint->ingredients[i].ingredientGrams, ingredientGramsPrintBuffer);
			snprintf(ingredientBuffer, 5, "%d)", i + 1);
			pdf_add_text(pdf, NULL, ingredientBuffer, V_FONT_POINTS, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
			//add the size in grams aligned right to the size of the largestIngredientSize buffer
			if (recipeToPrint->ingredients[i].ingredientGrams > 0)
				pdf_add_text_wrap(pdf, NULL, ingredientGramsPrintBuffer, V_FONT_POINTS, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, 0, PDF_BLACK, ingredientSizeOffset, PDF_ALIGN_RIGHT, NULL);
			memset(ingredientBuffer, 0, sizeof(ingredientBuffer));
			//print the ingredient w/ the () bracket info, if there is no info, print the recipe to buffer with out
			if (recipeToPrint->ingredients[i].nonWeighedIngredientFlag == 1){
				if (strlen(recipeToPrint->ingredients[i].userCupsInput) > 0)
					snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN * 2, "  %s (%s)", recipeToPrint->ingredients[i].ingredientName, recipeToPrint->ingredients[i].userCupsInput);
				else (snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN + 2, "  %s", recipeToPrint->ingredients[i].ingredientName));
			} else {
				if (strlen(recipeToPrint->ingredients[i].userCupsInput) > 0)
					snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN * 2, "  Grams Of %s (%s)", recipeToPrint->ingredients[i].ingredientName, recipeToPrint->ingredients[i].userCupsInput);
				else (snprintf(ingredientBuffer, INGREDIENT_BUFFER_LEN + 12, "  Grams Of %s", recipeToPrint->ingredients[i].ingredientName));
			}
			pdf_add_text(pdf, NULL, ingredientBuffer, V_FONT_POINTS, SIDE_MARGIN + ingredientSizeOffset, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
			linePointCounter += 1.25 * V_FONT_POINTS;
			lineCounter++;
		}
	}
	//add instructions
	linePointCounter += (2 * V_FONT_POINTS);
	pdf_add_text(pdf, NULL, "        INSTRUCTIONS:", V_FONT_POINTS, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
	linePointCounter += (1.5 * V_FONT_POINTS);
	char recipeToPDFBuffer[MAX_INGREDIENT_TEXT] = {'\0'};
	char recipeToPDFBufferNumbered[MAX_INGREDIENT_TEXT + 3] = {'\0'};
	for (int i = 0; i < recipeToPrint->numberOfInstructions; i++){
		float linesPerInstrctionCounter = 0.0;
		memset(recipeToPDFBuffer, 0, sizeof(recipeToPDFBuffer));
		memset(recipeToPDFBufferNumbered, 0, sizeof(recipeToPDFBufferNumbered));
		recipeBufferToPDFOutput(recipeToPDFBuffer, recipeToPrint->recipeInstructions[i]);
		snprintf(recipeToPDFBufferNumbered, 5, "%d)  ", i + 1);
		strcat(recipeToPDFBufferNumbered, recipeToPDFBuffer);
		pdf_add_text_wrap(pdf, NULL, recipeToPDFBufferNumbered, V_FONT_POINTS - 2, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, 0, PDF_BLACK, TOTAL_HORIZONTAL_POINTS - (2 * SIDE_MARGIN), PDF_ALIGN_LEFT, &linesPerInstrctionCounter);
		linePointCounter += (linesPerInstrctionCounter + (.5 * V_FONT_POINTS));
		//new page check
		if ((TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter < 128) && (recipeToPrint->numberOfInstructions - i > 2)){
			addNewPDFPage(pdf, recipeToPrint, &linePointCounter);
			pdf_add_text(pdf, NULL, "        INSTRUCTIONS (cont'd):", V_FONT_POINTS, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
			linePointCounter += (1.5 * V_FONT_POINTS);
		}
	}
	if ((TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter < 120) && (recipeToPrint->numberOfNotes > 1)){
		addNewPDFPage(pdf, recipeToPrint, &linePointCounter);
	}
	//add notes
	if (recipeToPrint->numberOfNotes > 0){
		linePointCounter += (2 * V_FONT_POINTS);
		pdf_add_text(pdf, NULL, "        NOTES:", V_FONT_POINTS, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
		linePointCounter += (1.5 * V_FONT_POINTS);
		for (int i = 0; i < recipeToPrint->numberOfNotes; i++){
			float linesPerNoteCounter = 0.0;
			memset(recipeToPDFBuffer, 0, sizeof(recipeToPDFBuffer));
			memset(recipeToPDFBufferNumbered, 0, sizeof(recipeToPDFBufferNumbered));
			recipeBufferToPDFOutput(recipeToPDFBuffer, recipeToPrint->recipeNotes[i]);
			snprintf(recipeToPDFBufferNumbered, 5, "%d)  ", i + 1);
			strcat(recipeToPDFBufferNumbered, recipeToPDFBuffer);
			pdf_add_text_wrap(pdf, NULL, recipeToPDFBufferNumbered, V_FONT_POINTS - 2, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, 0, PDF_BLACK, TOTAL_HORIZONTAL_POINTS - (2 * SIDE_MARGIN), PDF_ALIGN_LEFT, &linesPerNoteCounter);
			linePointCounter += (linesPerNoteCounter + (.25 * V_FONT_POINTS));
			if ((TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter < 128) && (recipeToPrint->numberOfNotes - i > 2)){
				addNewPDFPage(pdf, recipeToPrint, &linePointCounter);
				pdf_add_text(pdf, NULL, "        NOTES (cont'd):", V_FONT_POINTS, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
				linePointCounter += (1.5 * V_FONT_POINTS);
			}
		}
	}
	pdf_save_file(pdf, fp);
	pdf_destroy(pdf);
	fclose(fp);
}

/********************************************************************************************************************
* 																													*
*	  			prints the recipe name in a star-box at the PDF's top and recipe type at the bottom					*
*				advances the linePointCounter by the number of PDF lines used by the recipe name box				*
*																													*
*********************************************************************************************************************/
void printRecipeNameAndTypeToPDF(struct pdf_doc *pdf, struct recipeStruct *recipeToPrint, int *linePointCounter){
	int recipeNamePtLength = strlen(recipeToPrint->recipeName) * H_FONT_POINTS;
	int centerNameOffset = ((TOTAL_HORIZONTAL_POINTS - recipeNamePtLength )/ 2);
	//Add recipe name box
	pdf_add_text(pdf, NULL, "*********************************************************************************************************", 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - *linePointCounter, PDF_BLACK); //100 * chars
	*linePointCounter += (.5 *V_FONT_POINTS);
	pdf_add_text(pdf, NULL, "*                                                                                                                                                *", 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - *linePointCounter, PDF_BLACK);
	*linePointCounter += (.5 *V_FONT_POINTS);
	pdf_add_text(pdf, NULL, "*                                                                                                                                                *", 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - *linePointCounter, PDF_BLACK);
	*linePointCounter += (.5 *V_FONT_POINTS);
	pdf_add_text(pdf, NULL, "*                                                                                                                                                *", 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - *linePointCounter, PDF_BLACK);
	//overlay centered recipe name on same center box line
	pdf_add_text(pdf, NULL, recipeToPrint->recipeName, 14, centerNameOffset, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - *linePointCounter, PDF_BLACK);
	*linePointCounter += (.5 *V_FONT_POINTS);
	pdf_add_text(pdf, NULL, "*                                                                                                                                                *", 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - *linePointCounter, PDF_BLACK);
	*linePointCounter += (.5 *V_FONT_POINTS);
	pdf_add_text(pdf, NULL, "*                                                                                                                                                *", 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - *linePointCounter, PDF_BLACK);
	*linePointCounter += (.5 *V_FONT_POINTS);
	pdf_add_text(pdf, NULL, "*                                                                                                                                                *", 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - *linePointCounter, PDF_BLACK);
	*linePointCounter += (.5 *V_FONT_POINTS);
	pdf_add_text(pdf, NULL, "*********************************************************************************************************", 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - *linePointCounter, PDF_BLACK);
	*linePointCounter += (2.5 * V_FONT_POINTS);
	
	//print enum type on right side of screen
	char enumValue[12] = {'\0'};
	switch (recipeToPrint->recipeType){
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
	pdf_add_text_wrap(pdf, NULL, enumValue, V_FONT_POINTS, SIDE_MARGIN, 59, 0, PDF_BLACK, TOTAL_HORIZONTAL_POINTS - (2 * SIDE_MARGIN), PDF_ALIGN_RIGHT, NULL);
	pdf_add_text(pdf, NULL, "**********************************************************************************************************", 12, SIDE_MARGIN, 45, PDF_BLACK); 
}

/********************************************************************************************************************
* 																													*
*	  			adds a new page to the pdf with the recipe name in a star-box at the PDF's top and					*
*				recipe type at the bottom, resets linePointCounter to the total minus lines used for the box		*
*																													*
*********************************************************************************************************************/
void addNewPDFPage(struct pdf_doc *pdf, struct recipeStruct *recipeToPrint, int *linePointCounter){
	pdf_append_page(pdf);
	*linePointCounter = 0;
	printRecipeNameAndTypeToPDF(pdf, recipeToPrint, linePointCounter);
}
