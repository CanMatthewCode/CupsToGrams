#include <stdio.h>
#include <ctype.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"
#include "convertIngredient.h"


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
	clearScreen();
	//create head pointer and load ingredientType link list
	struct ingredientType *head = NULL;
	head = loadIngredientTypes();
	char menu = '\0';
	while (menu != 'Q'){
		clearScreen();
		puts("\t\t*****************************************************************");
		puts("\t\t*\t\t\t\t\t\t\t\t*");
		puts("\t\t*\t\t-RECIPE AND INGREDIENT CONVERTER-\t\t*");
		puts("\t\t*\t\t\t\t\t\t\t\t*");
		puts("\t\t*****************************************************************");
		puts("\n\t\tMain Menu Options:\n");
	
		puts("\t\t(1) Convert Ingredient\n\t\t(2) Convert Recipe\n\t\t"
			 "(3) See Ingredient List\n\t\t(4) See Recipe List"
			 "\n\t\t(Q) Quit");
		printf("\n\t\tEnter Selection : ");
		char menu = '\0';
		menu = getchar();
		menu = toupper(menu);
		switch (menu){
			case '1': 	clearScreen();
						head = convertIngredientMenu(head); //- leads to submenu to ask to search by name, by type, or all 
						//					 			  -- further submenu asks to add type of ingredient or add ingredient
						break; 
			case '2': 	//convertRecipe(); - leads to submenu to ask to convert recipe then to save or not
						break;
			case '3':	//printIngredients(); - leads to submenu to ask to search by name, by type, or all
						break;
			case '4':	//printRecipes(); - leads to submenu to ask to search by name, food type, or cuisine 
						break;
			case 'Q':	return 0;
			default: 	printf("\n\t\tInvalid Selection, Please Try Again\n");
		}
		while (getchar() != '\n')
			;
	}
	return 0;
}