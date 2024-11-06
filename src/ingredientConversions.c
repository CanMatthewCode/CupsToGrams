#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "ingredientConversions.h"


/********************************************************************************************************************
* 																													*
*	  			getCups Converts User Input in the form of Cups, Cups Part/Cups, or Cups.Parts to a float value		*
*																													*
*********************************************************************************************************************/
float getCups(char *amountToConvert){
	char inputBuffer[20] = {'\0'};
	strcpy(inputBuffer, amountToConvert);
	int cups = 0;
	int cupsNominator = 0;
	int cupsDenominator = 0;
	float totalCups = 0;
	//read the inputBuffer for all possible valid and invalid input possibilities: 
	//"Cups fractionPart/Cups", "fractionPart/Cups", or "Cups.percentCups" - valid
	//"cups cups", or "other" - invalid
	if (sscanf(inputBuffer, " %i %i/%i", &cups, &cupsNominator, &cupsDenominator) == 3){
		totalCups = cups + (float)(cupsNominator/(float)cupsDenominator);
	} else if (sscanf(inputBuffer, " %i/%i", &cupsNominator, &cupsDenominator) == 2){
		totalCups = (float)cupsNominator/(float)cupsDenominator;
	} else if (sscanf(inputBuffer, "%i %i", &cups, &cupsNominator) == 2){
		printf("Invalid input\n");
		return -1;
	} else if (sscanf(inputBuffer, "%f", &totalCups) == 1){
	} else {
		printf("Invalid input\n");
		return -1;
	}
	return totalCups;
}

/********************************************************************************************************************
* 																													*
*	 			read input into user buffer. must pass in a buffer[INGREDIENT_BUFFER_LEN]							*
*				upon completion, buffer will be filled by "Capitalized First Letter Syntax"							*
*																													*
*********************************************************************************************************************/
void readUserInputIntoBuffer(char buffer[INGREDIENT_BUFFER_LEN]){
	char *temp = buffer;
	char ch = '\0';
	int counter = 0;
	do{
	    ch = getchar();
	    if ((counter == 0) && (ch == '\n'))
    	    printf("\t\tInvalid Entry: ");
    } while (ch == '\n');
	while ((ch == ' ') || (ch == '\t') || (ch == '\n'))
		ch = getchar();
	ch = toupper(ch);
	*temp = ch;
	counter = 1;
	while ((ch = getchar()) != '\n' && counter < (INGREDIENT_BUFFER_LEN - 1)){
		ch = tolower(ch);
		if (ch == '\t')
		    ch = ' ';
		if (((ch == ' ') || (ch == '\t')) && ((*(temp+counter-1) == ' ')))
			continue;
		if (*(temp+counter-1) == ' ')
			ch = toupper(ch);
		*(temp+counter) = ch;
		counter++;
		if (counter == (INGREDIENT_BUFFER_LEN - 1)){
			printf("\n\n\t\tUser Input Is Too Long, Unusable Extra Was Removed\n\t\tHit Enter To Continue: ");
			while ((ch = getchar()) != '\n');
			while ((ch = getchar()) != '\n');
			break;
		}
	}
	if (*(temp+counter) == ' ')
		*(temp+counter) = '\0';  
}

/********************************************************************************************************************
* 																													*
*			  clearScreen prints an escape sequence to clear the terminal											*
*																													*
*********************************************************************************************************************/
void clearScreen(void){
	printf("\033[2J\033[H"); // ANSI escape sequence to clear screen
}

/********************************************************************************************************************
* 																													*
*	 		 parses user input to determine if they mean cups(c), tablespoons(tbsp) or teaspoons(tsp)				*
*			  returns the divisor number for the fraction of cups to calculate against								*
*			  return 0 on failure to get Cups, Tablespoons, or Teaspoons as input									*
*																													*
*********************************************************************************************************************/
int typeOfMeasurement(char *typeToConvert){
	if ((strcmp(typeToConvert, "Cups") == 0) || (strcmp(typeToConvert, "Cup") == 0) || (strcmp(typeToConvert, "C") == 0)){
		return 1;
	} else if ((strcmp(typeToConvert, "Tablespoons") == 0) || (strcmp(typeToConvert, "Tablespoon") == 0) || (strcmp(typeToConvert, "Tbsp") == 0) || (strcmp(typeToConvert, "Table") == 0)) {
		return 16;
    } else if ((strcmp(typeToConvert, "Teaspoons") == 0) || (strcmp(typeToConvert, "Teaspoon") == 0) || (strcmp(typeToConvert, "Tsp") == 0) || (strcmp(typeToConvert, "Tea") == 0)){
		return 48;
	} else 
	    return 0;
}

/********************************************************************************************************************
* 																													*
*			  parses a readUserInputIntoBuffer input in Cups notation and returns chosen ingredient amount in grams	*
*																													*
*********************************************************************************************************************/
float cupsToGrams(char *cupsInputAmountBuffer, struct ingredientItem *ingredientToConvert){
	char measurementAmount[20] = {'\0'};
	char measurementType[12] = {'\0'};
	int charsRead = 0;
	float sum = 0;
	char *currentPosition = NULL;
	printf("\n\n\t\tEnter Amount Of \'%s\' To Convert From US Cups Measurements: ", ingredientToConvert->ingredientName);
	do {
		memset(cupsInputAmountBuffer, 0, 20);
		memset(measurementAmount, 0, sizeof(measurementAmount));
		memset(measurementType, 0, sizeof(measurementType));
		charsRead = 0;
		readUserInputIntoBuffer(cupsInputAmountBuffer);
		currentPosition = cupsInputAmountBuffer;
		//move through cupsInputAmountBuffer reading the numbers then types in a loop
		do {
			if (sscanf(currentPosition, " %19[0-9/ ]%19[A-Za-z]%n", measurementAmount, measurementType, &charsRead) == 2) {
			//safety for if typeOfMeasurement returns 0 for wrong input
				if (typeOfMeasurement(measurementType) == 0){
					break;
				}
				sum += ((getCups(measurementAmount)) / (typeOfMeasurement(measurementType)));
				currentPosition += charsRead; 
			} else {
				break; //exit the loop if sscanf() fails to read two input items
			}
		} while (*currentPosition != '\0');
		if (ingredientToConvert->tablespoonFlag == 1)
			sum *= 16;
		if (sum == 0){
			printf("\n\t\t%s: Not Valid Input, Try Again: ", cupsInputAmountBuffer);
		}
	} while (sum == 0);
	return sum*ingredientToConvert->gramsPerCup;
}

/********************************************************************************************************************
* 																													*
*	  			accepts user input only if it is numeric and within -999 to 999 bounds								*
*																													*
********************************************************************************************************************/
int getNumericChoice(void){
    char buffer[5];
    long int number;
    char *endptr;
    int ch;
    while (1) {
        while ((ch = getchar()) == ' ' || ch == '\t')
            ;
        // Check for immediate newline
        if (ch == '\n') {
            printf("\t\tInvalid Entry: ");
            continue;
        }
        // Put back the non-whitespace character
        ungetc(ch, stdin);
        // Read input
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\t\tInvalid Entry: ");
            continue;
        }

        // Check for buffer overflow
        if (strchr(buffer, '\n') == NULL) {
            printf("\t\tInvalid Entry: ");
            // Clear the rest of the input
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
        // Convert to number
        number = strtol(buffer, &endptr, 10);
        if (endptr == buffer) {
            printf("\t\tInvalid Entry: ");
            continue;
        }
        return (int)number;
    }
}