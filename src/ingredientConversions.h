#ifndef INGREDIENTCONVERSIONS_H
#define INGREDIENTCONVERSIONS_H

#include <stdio.h>
#include <ctype.h>

#define INGREDIENT_BUFFER_LEN 30
#define MAX_INGREDIENTS_FOUND 100

#define YESNOCHOICE(choice)												\
do {								    								\
	int c;																\
	(choice) = '\0';													\
	while ((((c) = getchar()) != EOF) && ((c) != '\n')) {				\
		if (((choice) == '\0') && ((c) != ' ') && ((c) != '\t')) {		\
			(choice) = toupper((c));									\
		}																\
	}																	\
	if (((choice) != 'Y') && ((choice) != 'N')) {						\
		printf("\t\tInvalid Entry: ");									\
	}																	\
} while (((choice) != 'Y') && ((choice) != 'N'))

//#define clearScreen														\
//	printf("\033[2J\033[H");

struct ingredientItem{
	char ingredientName[INGREDIENT_BUFFER_LEN];
	int tablespoonFlag;
	float gramsPerCup;
	struct ingredientItem *prev;
	struct ingredientItem *next;	
};

struct ingredientType{
	char typeName[INGREDIENT_BUFFER_LEN];
	struct ingredientItem *head;
	struct ingredientType *prev;
	struct ingredientType *next;
};

/************************************************************************************************************
* 																											*
*	  getCups Converts User Input in the form of Cups, Cups Part/Cups, or Cups.Parts to a float value		*
*																											*
*************************************************************************************************************/
float getCups(char *amountToConvert);

/************************************************************************************************************
* 																											*
*	  cupsToGrams Accepts Number of Cups from getCups and Grams Per Cup from ingredientItem->gramsPerCup	*
*																											*
*************************************************************************************************************/
float cupsToGrams(float cups, float gramsPerCup);

/************************************************************************************************************
* 																											*
*	 	read input into user buffer. must pass in a buffer[INGREDIENT_BUFFER_LEN]							*
*		upon completion, buffer will be filled by "Output"													*
*																											*
*************************************************************************************************************/
void readUserInputIntoBuffer(char buffer[INGREDIENT_BUFFER_LEN]);

/************************************************************************************************************
* 																											*
*	  clearScreen prints an escape sequence to clear the terminal											*
*																											*
*************************************************************************************************************/
void clearScreen(void);

/************************************************************************************************************
* 																											*
*	  parses user input to determine if they mean cups(c), tablespoons(tbsp) or teaspoons(tsp)				*
*	  returns the divisor number for the fraction of cups to calculate against								*
*																											*
*************************************************************************************************************/
int typeOfMeasurement(char *typeToConvert);

/************************************************************************************************************
* 																											*
*	  	accepts user input only if it is numeric and within -999 to 999 bounds								*
*																											*
*************************************************************************************************************/
int getNumericChoice();


#endif //INGREDIENTCONVERSIONS_H