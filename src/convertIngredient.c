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
	
		puts("\t\t(1) Convert Ingredient\n\t\t(2) Search For Ingredient\n\t\t"
			 "(3) See Ingredients By Type\n\t\t(4) See Ingredient Types\n\t\t"
			 "(5) Add Ingredient Type\n\t\t(6) Delete Ingredient Type\n\t\t"
			 "(7) Add Ingredient\n\t\t"
			 "(B) Back");
		printf("\n\t\tEnter Selection : ");
		
		char menu = '\0';
		menu = getchar();
		menu = toupper(menu);
		switch (menu){
			case '1':	//search for input along loop of linked-list ingredientType->ingredientItems then use input for conversion
			case '2':	//search for input along loop of linked-list ingredientType->ingredientItems and print out value, then ask for conversion
						break;
						//print ingredientItem linked list from ingredientType node
			case '3': 	break;
			case '4': 	clearScreen();
						printIngredientTypeList(headPointer);
						break; 
			case '5':	clearScreen();
						headPointer = addIngredientType(headPointer);
						break;
			case '6':	clearScreen();
						headPointer = deleteIngredientTypeNode(headPointer);
						break;
			case '7':	clearScreen();
						headPointer = addIngredient(headPointer);
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

/************************************************************************************************************
* 																											*
*				add a node to the ingredientItem linked-list from the convert ingredient menu				*
*				enter ingredient type to access linked-list type. returns pointer to head of Typelist 		*
*																											*
*************************************************************************************************************/
struct ingredientType *addIngredient(struct ingredientType *head){
//ask for the ingredient type, take input and use searchIngredientType to find the node with the head pointer for that type
//offer to print types, then put in type.  use the buffer to find the node type, when it's found, ask for input, if not found say not found
//then show how input is wanted and ask for input first for weight then for cups or tbsp.  Ask for confirmation
//link it into the right list, ask for more.  if not, moves the sub list to the head, dumps the sub linked list, then resets to head and
//links the head back to the type node, reset the type nodes back to head 
//return headPointer to the overall ingredientType link list
	char ingredientTypeBuffer[INGREDIENT_BUFFER_LEN]={'\0'};
	struct ingredientType *cur = head;
}