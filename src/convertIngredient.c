#include <stdio.h>
#include <ctype.h>
#include "convertIngredient.h"
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"

/************************************************************************************************************
* 																											*
*				functionality for the ingredientType linked-list from the main menu option					*
*																											*
*************************************************************************************************************/
struct ingredientType *convertIngredientMenu(struct ingredientType *head){
	char menu = '\0';
	struct ingredientType *headPointer = head;
	//struct ingredientItem *itemHead;
	while (getchar() != '\n')
		;
	while (menu != 'B'){
		clearScreen();
		puts("\t\t*****************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t      -CONVERT INGREDIENT- \t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t*");
		puts("\t\t*****************************************************************");
		puts("\n\t\tMenu Options:\n");
	
		puts("\t\t(1) See Ingredient Types\n\t\t(2) Add Ingredient Type\n\t\t"
			 "(3) See Ingredients By Type\n\t\t(4) Delete Ingredient Type\n\t\t"
			 "(B) Back");
		printf("\n\t\tEnter Selection : ");
		
		char menu = '\0';
		menu = getchar();
		menu = toupper(menu);
		switch (menu){
			case '1': 	clearScreen();
						printIngredientTypeList(headPointer);
						break; 
			case '2': 	clearScreen();
						headPointer = addIngredientType(headPointer);
						break;
			case '3':	//print ingredientItem linked list from ingredientType node
						break;
			case '4':	clearScreen();
						headPointer = deleteIngredientTypeNode(headPointer);
						break;
			case 'B':	return head;
			default: 	;
		}
		while (getchar() != '\n')
			;
	}
}

/************************************************************************************************************
* 																											*
*				add a node to the ingredientType linked-list from the convert ingredient menu				*
*				returns pointer to head of list 															*
*																											*
*************************************************************************************************************/
struct ingredientType *addIngredientType(struct ingredientType *head){
	 char choice = '\0';
	 while (choice != 'N'){
		clearScreen();
		choice = '\0';
		struct ingredientType *headPointer = head;
		char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
		puts("\t\t*****************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t      -ADD INGREDIENT TYPE- \t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t*");
		puts("\t\t*****************************************************************");
		printf("\n\n\t\tEnter Ingredient Type to Add: ");
	 	readUserInputIntoBuffer(buffer);
		headPointer = addNewIngredientTypeNode(headPointer, buffer);
		printf("\n\t\tAdd Another Ingredient Type (y/n)?");
		choice = getchar();
		choice = toupper(choice);
		switch (choice){
			case 'Y' :	break;
			case 'N' :	dumpIngredientTypeList(headPointer);
						return headPointer;
			default	 : 	printf("Invalid Entry\n");
		}
	}
}

