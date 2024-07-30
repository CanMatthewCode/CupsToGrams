#include <stdio.h>
#include <ctype.h>
#include "ingredientMenus.h"
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"

/************************************************************************************************************
* 																											*
*				functionality for the ingredientType linked-list from the main menu option					*
*																											*
*************************************************************************************************************/
struct ingredientType *convertIngredientMenu(struct ingredientType *head){
	char menu = '\0';
	struct ingredientType *headPointer = head;
	//struct ingredientItem *itemHead;
	while (getchar() != '\n');
	clearScreen();
	do {
		clearScreen();
		puts("\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t      -CONVERT INGREDIENT- \t\t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		puts("\n\t\tMenu Options:\n");
	
		puts("\t\t(1) Convert Ingredient\n\t\t(2) Search For Ingredient\n\t\t"
			 "(3) See Ingredients By Type\n\t\t(4) See Ingredient Types\n\t\t"
			 "(5) Add Ingredient Type\n\t\t(6) Delete Ingredient Type\n\t\t"
			 "(7) Add Ingredient\n\t\t"
			 "(B) Back");
		printf("\n\t\tEnter Selection: ");
		char menu = '\0';
		menu = toupper(getchar());
		switch (menu){
			case '1':	//search for input along loop of linked-list ingredientType->ingredientItems then use input for conversion
			case '2':	//search for input along loop of linked-list ingredientType->ingredientItems and print out value, then ask for conversion
						break;
						//print ingredientItem linked list from ingredientType node
			case '3': 	break;
			case '4': 	clearScreen();
						printIngredientTypeList(headPointer);
						printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t(Press Enter to Continue)");
						while (getchar() !='\n');
						break; 
			case '5':	clearScreen();
						headPointer = addIngredientType(headPointer);
						break;
			case '6':	clearScreen();
						headPointer = deleteIngredientTypeNode(headPointer);
						break;
			case '7':	clearScreen();
						addIngredientItem(headPointer);
						break;
			case 'B':	return headPointer;
			default: 	clearScreen();
						printf("\n\t\tInvalid Selection, Try Again\n");
		}
		while (getchar() != '\n');
	} while (menu != 'B');
	return headPointer;
}

/************************************************************************************************************
* 																											*
*				add a node to the ingredientType linked-list from the convert ingredient menu				*
*				returns pointer to head of list 															*
*																											*
*************************************************************************************************************/
struct ingredientType *addIngredientType(struct ingredientType *head){
	 char choice = '\0';
	 struct ingredientType *headPointer = head;
	 do {
		clearScreen();
		choice = '\0';

		char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
		puts("\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t      -ADD INGREDIENT TYPE- \t\t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		printf("\n\n\t\tEnter Ingredient Type To Add: ");
	 	readUserInputIntoBuffer(buffer);
		headPointer = addNewIngredientTypeNode(headPointer, buffer);
		char innerChoice = '\0';
		do{
			innerChoice = '\0';
			printf("\n\t\tAdd Another Ingredient Type (y/n)?");
			innerChoice = toupper(getchar());
			if ((innerChoice != 'Y') && (innerChoice != 'N'))
				printf("\t\tInvalid Entry\n");
		} while ((innerChoice != 'Y') && ((innerChoice) != 'N'));
		choice = innerChoice;
	} while (choice != 'N');
	dumpIngredientTypeList(headPointer);
	return headPointer;
}

/************************************************************************************************************
* 																											*
*				add a node to the ingredientItem linked-list from the convert ingredient menu				*
*				enter ingredient type to access linked-list type. returns pointer to head of Typelist 		*
*																											*
*************************************************************************************************************/

void addIngredientItem(struct ingredientType *head){
	char choice = '\0';
	char innerChoice = '\0';
	char ingredientTypeBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	char ingredientItemBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	do {
		struct ingredientType *headPointer = head;
		struct ingredientType *foundIngredientType = NULL;
		clearScreen();
		choice = '\0';
		puts("\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t      -ADD NEW INGREDIENT- \t\t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		do {
			memset(ingredientTypeBuffer, 0, sizeof(ingredientTypeBuffer));
			printf("\n\n\t\tEnter The Food Type Of The Ingredient You Wish To Add: ");
	 		readUserInputIntoBuffer(ingredientTypeBuffer);
	 		foundIngredientType = (findIngredientType(headPointer, ingredientTypeBuffer));
	 		if (foundIngredientType == NULL){
	 			printf("\n\t\tFood Type Not Found:");
	 			printf("Print Full Food Types List (y/n)? ");
	 			do{
	 				innerChoice = '\0';
					innerChoice = toupper(getchar());
					while (getchar() != '\n')
						;
					if ((innerChoice != 'Y') && (innerChoice != 'N'))
						printf("\n\t\tInvalid Entry, Try Again: ");
					if (innerChoice == 'Y'){
						printIngredientTypeList(head);
						printf("\n\n");
					}
				} while ((innerChoice != 'N') && (innerChoice != 'Y'));	
			}
		} while (foundIngredientType == NULL);
		//loop of inputting ingredients in this type of item, when they say no more of this type, dump this type into .txt file
		do {
			choice = '\0';
			memset(ingredientItemBuffer, 0, sizeof(ingredientItemBuffer));
			printf("\n\t\tEnter New Ingredient Name: ");
			readUserInputIntoBuffer(ingredientItemBuffer);
			if (findIngredientItemNode(headPointer, ingredientItemBuffer) != NULL){
				printf("\t\tIngredient Already Exists (Press Enter to Continue):");
			//relink changed head back to where the ingredientType node the ingredientItem linked-list attaches
			} else (foundIngredientType->head = addNewIngredientItemNode(foundIngredientType->head, ingredientItemBuffer));
			while (getchar() != '\n');
			printf("\n\n\t\tAdd Another Ingredient Of The Same Food Type (y/n)? ");
			while ((choice != 'Y') && (choice != 'N')){
				choice = '\0';
				choice = toupper(getchar());
				if ((choice != 'Y') && (choice != 'N')){
					printf("\t\tInvalide Entry, Try Again: ");
					while (getchar() != '\n');
				}
			}
		} while (choice != 'N');
		dumpIngredientItemList(foundIngredientType);
		//then outer loop asking if there is a different ingredient type to add and start the inner loop again if they say yes.  if no, exit
		while (getchar() != '\n');
		printf("\n\n\t\tAdd An Ingredient For A Different Type Of Food (y/n)? ");
		do {
			choice = '\0';
			choice = toupper(getchar());
			if ((choice != 'Y') && (choice != 'N')){
				printf("\t\tInvalid Entry\n");
				while (getchar() != '\n');
			}
		} while ((choice != 'Y') && (choice != 'N'));
	} while (choice != 'N');
}
