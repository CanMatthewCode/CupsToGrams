#ifndef INGREDIENTCONVERSIONS_H
#define INGREDIENTCONVERSIONS_H

#include <stdio.h>
#include <ctype.h>

#define INGREDIENT_BUFFER_LEN 50
#define MAX_INGREDIENTS_FOUND 100
#define NUMBER_OF_CHARS_ON_SCREEN 81

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

//#define CLEARSCREEN													\
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


/********************************************************************************************************************
* 																													*
*	 		 getCups Converts User Input in the form of Cups, Cups Part/Cups, or Cups.Parts to a float value		*
*																													*
*********************************************************************************************************************/
float getCups(char *amountToConvert);

/********************************************************************************************************************
* 																													*
*	 			read input into user buffer. must pass in a buffer[INGREDIENT_BUFFER_LEN]							*
*				upon completion, buffer will be filled by "Capitalized First Letter Syntax"							*
*				Returns the number of chars read into buffer														*
*																													*
*********************************************************************************************************************/
int readUserInputIntoBuffer(char buffer[INGREDIENT_BUFFER_LEN]);

/********************************************************************************************************************
* 																													*
*	  			clearScreen prints an escape sequence to clear the terminal											*
*																													*
*********************************************************************************************************************/
void clearScreen(void);

/********************************************************************************************************************
* 																													*
*	 		 parses user input to determine if they mean cups(c), tablespoons(tbsp) or teaspoons(tsp)				*
*			  returns the divisor number for the fraction of cups to calculate against								*
*			  return 0 on failure to get Cups, Tablespoons, Teaspoons, Pounds, or Ozs as input						*
*			use the weighedInputFlag set to 1 when converting weight rather than volume measurements				*
*			  and set to 2 if grams are inputted directly															*
*																													*
*********************************************************************************************************************/
float typeOfMeasurement(char *typeToConvert, int *weighedInputFlag);

/********************************************************************************************************************
* 																													*
*	  		parses a readUserInputIntoBuffer input in Cups notation and outputs chosen ingredient amount in grams	*
*																													*
*********************************************************************************************************************/
float cupsToGrams(char *cupsInputAmountBuffer, struct ingredientItem *ingredientToConvert);

/********************************************************************************************************************
* 																													*
*			  parses a readUserInputIntoBuffer input in weight notation and returns amount in grams					*
*																													*
*********************************************************************************************************************/
float weightToGrams(char *cupsInputAmountBuffer, char *ingredientName);

/********************************************************************************************************************
* 																													*
*	  			accepts user input only if it is numeric and within -999 to 999 bounds								*
*																													*
*********************************************************************************************************************/
int getNumericChoice();

/********************************************************************************************************************
* 																													*
*	  			takes a recipeStruct's ingredientStruct member and checks to see if it's ingredientGrams			*
*				member has trailing zeros and removes all for printing if so										*
*																													*
*********************************************************************************************************************/
void decimalPlaceCheck(float ingredientGrams, char *bufferToFill);

/********************************************************************************************************************
* 																													*
*	  			takes the parsed user input for amount and amount type and unifies it into a 						*
*				standard notation. Uses cupAmount return from user input to check for plurality						*
*																													*
*********************************************************************************************************************/
void unifyMeasurementTypes(char *cupsInputAmountBuffer, char *measurementAmount, char *typeToConvert, float cupAmount);

#endif //INGREDIENTCONVERSIONS_H
