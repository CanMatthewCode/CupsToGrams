#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"
#include "ingredientMenus.h"
#include "recipeMenus.h"
#include "recipeSystemCheck.h"
 
int main (int argc, char **argv){
	//create head pointer and load ingredientType linked-list then sub linked-lists
	struct ingredientType *ingredientHead = NULL;
	struct recipeStruct *recipeHead = NULL;
	int adminFlag = 0;
	if (argc > 1 && strcmp(argv[1], "ADMIN") == 0){
		adminFlag = 1;
	}
	setExePath();
	ingredientHead = loadIngredientTypes();
	recipeHead = loadRecipesToLinkedList();
	if (ingredientHead)
		ingredientHead = loadAllIngredientTypeSubLists(ingredientHead);
	char menu = '\0';
	do {
		clearScreen();
		puts("\n\n\t\t*********************************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t\t-RECIPE AND INGREDIENT CONVERTER-\t\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
		puts("\t\t*********************************************************************************");
		puts("\n\n\t\tMain Menu Options:\n");
	
		puts("\t\t(1) Recipe Conversions\n\t\t(2) See Saved Recipes"
			 "\n\t\t(3) Convert An Ingredient\n\t\t(4) See Ingredient Lists"
			 "\n\n\t\t(Q) Quit");
		printf("\n\n\t\tEnter Selection: ");
		do {
        	menu = toupper(getchar());
        	if (menu == '\n'){
            	printf("\t\tInvalid Selection: ");
            	continue;
        	}
        	while (getchar() != '\n');
			if (strchr("1234Q", menu) == NULL)
				printf("\t\tInvalid Selection: ");
    	} while (strchr("1234Q", menu) == NULL);
		switch (menu){
			case '1': 	recipeMenus(recipeHead, ingredientHead);
						break;
			case '2':	recipeHead = printSavedRecipeMenus(recipeHead, ingredientHead);
						break;
			case '3': 	clearScreen();
						ingredientHead = convertIngredientMenu(ingredientHead, adminFlag); 
						break; 
			case '4':	clearScreen();
						printAllIngredientItemsInTypeNode(ingredientHead);
						break;
			case 'Q':	if (ingredientHead)
							freeIngredientItemList(ingredientHead);
						if (ingredientHead)
							freeIngredientTypeList(ingredientHead);
						if (recipeHead)
							freeRecipeStructList(recipeHead);
						return 0;
			default: 	printf("\n\t\t\t\t\t***Invalid Selection***\n\n");
		}
	} while (menu != 'Q');
	return 0;
}
