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
			 "(5) Add Ingredient\n\t\t(6) Modify Ingredient\n\t\t"
			 "(7) Delete Ingredient\n\t\t(8) Add Ingredient Type\n\t\t"
			 "(9) Delete Ingredient Type\n\t\t(B) Back");
		printf("\n\t\tEnter Selection: ");
		char menu = '\0';
		menu = toupper(getchar());
		switch (menu){
			case '1':	//search for input along loop of linked-list ingredientType->ingredientItems then use input for conversion
						break;
			case '2':	findIngredient(headPointer);
						break;
			case '3': 	clearScreen();
						printAllIngredientItemsInTypeNode(headPointer);
						break;
			case '4': 	clearScreen();
						printIngredientTypeList(headPointer);
						printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t(Press Enter to Continue)");
						while (getchar() !='\n');
						break; 
			case '5':	clearScreen();
						addIngredientItem(headPointer);
						break;
			case '6':	clearScreen();
						modifyIngredientItem(headPointer);
						break;
			case '7':	clearScreen();
						deleteIngredientItem(headPointer);
						break;
			case '8':	clearScreen();
						headPointer = addIngredientType(headPointer);
						break;
			case '9':	clearScreen();
						headPointer = deleteIngredientTypeNode(headPointer);
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
	 			printf("\n\t\tFood Type Not Found, Print Full Food Types List (y/n)? ");
	 			do{
	 				innerChoice = '\0';
					innerChoice = toupper(getchar());
					while (getchar() != '\n');
					if ((innerChoice != 'Y') && (innerChoice != 'N'))
						printf("\n\t\tInvalid Entry, Try Again: ");
					if (innerChoice == 'Y'){
						printf("\n\n\n");
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
			if (findIngredientItemNode(headPointer, ingredientItemBuffer, NULL) != NULL){
				printf("\t\tIngredient Already Exists (Press Enter to Continue):");
			//relink changed head back to where the ingredientType node the ingredientItem linked-list attaches
			} else (foundIngredientType->head = addNewIngredientItemNode(foundIngredientType->head, ingredientItemBuffer));
			while (getchar() != '\n');
			printf("\n\n\t\tAdd Another Ingredient Of The Same Food Type (y/n)? ");
			while ((choice != 'Y') && (choice != 'N')){
				choice = '\0';
				choice = toupper(getchar());
				if ((choice != 'Y') && (choice != 'N')){
					printf("\t\tInvalid Entry, Try Again: ");
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
				printf("\t\tInvalid Entry: ");
				while (getchar() != '\n');
			}
		} while ((choice != 'Y') && (choice != 'N'));
	} while (choice != 'N');
}

/************************************************************************************************************
* 																											*
*				find any ingredient item node that matches partially with user input				 		*
*				if multiple options found, give options, then print chosen node								*
*																											*
*************************************************************************************************************/
void findIngredient(struct ingredientType *head){
	char choice = '\0';
	char ingredientItemBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	do {
		struct ingredientType *headPointer = head;
		struct ingredientItem *foundIngredient = NULL;
		memset(ingredientItemBuffer, 0, sizeof(ingredientItemBuffer)); 
		clearScreen();
		choice = '\0';
		puts("\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t      -FIND INGREDIENT- \t\t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		printf("\n\n\t\tEnter Ingredient Name: ");
		readUserInputIntoBuffer(ingredientItemBuffer);
		foundIngredient = findIngredientItemNode(headPointer, ingredientItemBuffer, NULL);
		//safety in case no ingredient was found and foundIngredient == NULL
		if (foundIngredient){
			printf("\n\n\n");	
			printIngredientItemNode(foundIngredient);
		}
		if (!foundIngredient)
			printf("\n\n\t\tIngredient Not Found");
		printf("\n\n\n\t\tFind Another Ingredient (y/n)? ");
		do {
			choice = '\0';
			choice = toupper(getchar());
			if ((choice != 'Y') && (choice != 'N')){
				printf("\t\tInvalid Entry ");
				while (getchar() != '\n');
			}
		} while ((choice != 'Y') && (choice != 'N'));
	} while (choice != 'N');
}

/************************************************************************************************************
* 																											*
*				print all ingredient items from sub-list stored in an ingredientType node					*
*																											*
*************************************************************************************************************/
void printAllIngredientItemsInTypeNode(struct ingredientType *head){
	char choice = '\0';
	char ingredientTypeBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	do {
		struct ingredientType *headPointer = head;
		struct ingredientType *foundIngredientType = NULL;
		memset(ingredientTypeBuffer, 0, sizeof(ingredientTypeBuffer));
		clearScreen();
		choice = '\0';
		puts("\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t      -INGREDIENTS BY FOOD TYPE- \t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		printf("\n\n\t\tEnter Desired Type Of Ingredient For Full List: ");
		readUserInputIntoBuffer(ingredientTypeBuffer);
		foundIngredientType = findIngredientType(headPointer, ingredientTypeBuffer);
	 	if (!foundIngredientType){
	 		char innerChoice = '\0';
	 		printf("\n\t\tFood Type Not Found: ");
	 		printf("Print Full Food Types List (y/n)? ");
	 		do{
	 			innerChoice = '\0';
				innerChoice = toupper(getchar());
				while (getchar() != '\n');
				if ((innerChoice != 'Y') && (innerChoice != 'N'))
					printf("\n\t\tInvalid Entry: ");
				if (innerChoice == 'Y'){
					printIngredientTypeList(head);
					printf("\n\n");
				}
			} while ((innerChoice != 'N') && (innerChoice != 'Y'));
		}
		if (foundIngredientType)
			printAllIngredientItemNodes(foundIngredientType);
		printf("\n\n\t\tPrint Another Type Of Ingredient (y/n)? ");
		do {
			choice = '\0';
			choice = toupper(getchar());
			if ((choice != 'Y') && (choice != 'N')){
				printf("\n\t\tInvalid Entry: ");
				while (getchar() != '\n');
			}
		} while ((choice != 'Y') && (choice != 'N'));
	} while (choice != 'N');
}

/************************************************************************************************************
* 																											*
*				modify an ingredientItem node's name, weight, tablespoonFlag								*
*																											*
*************************************************************************************************************/
void modifyIngredientItem(struct ingredientType *head){
	char choice = '\0';
	char ingredientItemBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	struct ingredientType *headPointer = NULL;
	struct ingredientItem *foundIngredient = NULL;
	//pointer to ingredientType which stores the head of the found ingredientItem that is to be modified
	struct ingredientType *foundIngredientsTypeNode = NULL;
	do {
		headPointer = head;
		foundIngredient = NULL;
		memset(ingredientItemBuffer, 0, sizeof(ingredientItemBuffer));
		clearScreen();
		choice = '\0';
		puts("\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t      -MODIFY INGREDIENT- \t\t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		do {
			printf("\n\n\t\tEnter Ingredient Name You Wish To Modify: ");
			memset(ingredientItemBuffer, 0, sizeof(ingredientItemBuffer));
			foundIngredientsTypeNode = NULL;
			readUserInputIntoBuffer(ingredientItemBuffer);
			foundIngredient = findIngredientItemNode(headPointer, ingredientItemBuffer, &foundIngredientsTypeNode);
			if(!foundIngredient){
				printf("\n\n\t\tIngredient Not Found. Enter New Ingredient Name (y/n)? ");
				do {
					choice = '\0';
					choice = toupper(getchar());
					if ((choice != 'Y') && (choice != 'N')){
						printf("\n\t\tInvalid Entry: ");
						while (getchar() != '\n');
					}
				} while ((choice != 'Y') && (choice != 'N'));
			}
		} while (!foundIngredient && (choice != 'N'));
		if (foundIngredient){
			char innerChoice = '\0';
			int changeChoice = 0;
			do{ 
				innerChoice = '\0';
				printf("\n\n");
				printIngredientItemNode(foundIngredient);
				printf("\n\n\t\t1) Change Name\n\t\t2) Change Weight\n\t\t"
				"3) Change Measurement Type\n\t\t4) Exit Without Change");
				printf("\n\n\t\tWhat Would You Like To Do? ");
				changeChoice = 0;
				do {
					changeChoice = 0;
					if ((scanf(" %i", &changeChoice) != 1) || (changeChoice < 1) || (changeChoice > 4)){
						printf("\n\n\t\tInvalid Entry: ");
						while (getchar() != '\n');
					}
				while (getchar() != '\n');
				} while ((changeChoice < 1) || (changeChoice > 4));
				switch (changeChoice){
					case 1:		modifyIngredientItemNodeName(foundIngredient);
								break;
					case 2:		modifyIngredientItemNodeWeight(foundIngredient);
								break;
					case 3:		modifyIngredientItemNodeFlag(foundIngredient);
								break;
					case 4:		innerChoice = 'N';
								break;
					default:	break; //should be no default - written here for clarity
				}
				while ((innerChoice != 'Y') && (innerChoice != 'N')){
					printf("\n\n\t\tWould You Like To Make Another Change (y/n)? ");
					while (getchar() != '\n');
					do {
						innerChoice = '\0';
						innerChoice = toupper(getchar());
						if ((innerChoice != 'Y') && (innerChoice != 'N')){
							printf("\n\t\tInvalid Entry: ");
							while (getchar() != '\n');
						}
					} while ((innerChoice != 'Y') && (innerChoice != 'N'));
				}
			} while (innerChoice != 'N');
			while (getchar() != '\n');
			dumpIngredientItemList(foundIngredientsTypeNode);
			printf("\n\n\t\tWould You Like To Modify A Different Ingredient (y/n)? ");
			do {
				choice = '\0';
				choice = toupper(getchar());
				if ((choice != 'Y') && (choice != 'N')){
					printf("\n\t\tInvalid Entry: ");
					while (getchar() != '\n');
				}
			} while ((choice != 'Y') && (choice != 'N'));
		}
	} while (choice != 'N');
}

/************************************************************************************************************
* 																											*
*				delete an ingredientItem node permanently from an ingredientItem linked list				*
*																											*
*************************************************************************************************************/
void deleteIngredientItem (struct ingredientType *head){
	struct ingredientItem *itemToBeDeleted = NULL;
	struct ingredientType *itemToBeDeletedsAttachedTypeNode = NULL;
	char ingredientItemBuffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	char choice = '\0';
	do {
		memset(ingredientItemBuffer, 0, sizeof(ingredientItemBuffer));
		choice = '\0';
		clearScreen();
		puts("\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		puts("\t\tx\t\t\t\t\t\t\t\t\t\tx");
		puts("\t\tx\t\t\t      -DELETE INGREDIENT- \t\t\t\tx");
		puts("\t\tx\t\t\t\t\t\t\t\t\t\tx");
		puts("\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		printf("\n\n\t\tEnter Name Of Ingredient You Wish To PERMANENTLY DELETE: ");
		readUserInputIntoBuffer(ingredientItemBuffer);
		itemToBeDeleted = findIngredientItemNode(head, ingredientItemBuffer, &itemToBeDeletedsAttachedTypeNode);
		if (!itemToBeDeleted){
			printf("\n\n\t\tIngredient Not Found");
		}
		if (itemToBeDeleted)
			deleteIngredientItemNode(itemToBeDeleted, itemToBeDeletedsAttachedTypeNode);
		while (getchar() != '\n');
		printf("\n\n\t\tWould You Like To Delete Another Ingredient (y/n)? ");
		do {
				choice = '\0';
				choice = toupper(getchar());
				if ((choice != 'Y') && (choice != 'N')){
					printf("\n\t\tInvalid Entry: ");
					while (getchar() != '\n');
				}
			} while ((choice != 'Y') && (choice != 'N'));
	} while (choice != 'N');
} 