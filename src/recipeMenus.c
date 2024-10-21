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

