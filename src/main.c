#include <stdio.h>
#include <ctype.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"
#include "ingredientMenus.h"
#include "recipeMenus.h"


/*		switch statement and functionality to do the following:
 *		1)  Convert ingredient
 *				1.a) add new ingredient to list		
 *		2)  Convert Recipe	
 *				2.a) add new recipe to List 
 *		3)  See Ingredient List
 *				3.a) Search Ingredient List visually
 *				3.b) Search Ingredient List by buffer input
 *		4)  See Recipe List
 *				4.a) Search Recipe List
 *				4.b) Search Recipe List By Food Type (steak, chicken, veg, baking, etc)
 *				4.c) Search Recipe List By Cuisine Type (Italian, French, Chinese, etc)
 *					4.a) print selected recipe
 */
 
/*		1) Convert ingredient
 *			1.1) Loop to open file pointers & load linked lists
 *			1.2) Loop to search through each ingredientType node list
 *			1.3) Return convert ingredient with found conversion amount
 *			1.4) If ingredient not found, option to add ingredient
 *				1.4a) If ingredient added, dump linked-list to text file to save
 *			1.5) Exit convert ingredient
 */
 
int main (int argc, char **argv){
	//create head pointer and load ingredientType linked-list then sub linked-lists
	struct ingredientType *ingredientHead = NULL;
	struct recipeStruct *recipeHead = NULL;
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
		puts("\n\t\tMain Menu Options:\n\n");
	
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
			case '2':	printAllRecipeNames(recipeHead);
						break;
						//- leads to submenu to ask to search by name, food type, or cuisine 
			case '3': 	clearScreen();
						ingredientHead = convertIngredientMenu(ingredientHead); 
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