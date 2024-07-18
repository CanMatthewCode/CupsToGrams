#include <stdio.h>
#include <ctype.h>
#include "ingredientConversions.h"


/************************************************************************************************************
* 																											*
*	  getCups Converts User Input in the form of Cups, Cups Part/Cups, or Cups.Parts to a float value		*
*																											*
*************************************************************************************************************/
float getCups(void){
	char inputBuffer[20] = {'\0'};
	int counter = 0;
	char c = '\0';
	int cups = 0;
	int cupsNominator = 0;
	int cupsDenominator = 0;
	float totalCups = 0;
	
	printf("Enter number of cups: ");
	//read character input until you fill the buffer or get to new line
	while (((c = getchar()) != '\n') && (counter < 20)){
		inputBuffer[counter] = c;
		counter++;
	}
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

/************************************************************************************************************
* 																											*
*	  cupsToGrams Accepts Number of Cups from getCups and Grams Per Cup from ingredientItem->gramsPerCup	*
*																											*
*************************************************************************************************************/
float cupsToGrams(float cups, float gramsPerCup){
	return cups * gramsPerCup;
}

/************************************************************************************************************
* 																											*
*	 	read input into user buffer. must pass in a buffer[INGREDIENT_BUFFER_LEN]							*
*		upon completion, buffer will be filled by "Capitalized First Letter Syntax"							*
*																											*
*************************************************************************************************************/
void readUserInputIntoBuffer(char buffer[INGREDIENT_BUFFER_LEN]){
	char *temp = buffer;
	char ch = '\0';
	ch = getchar();
	while ((ch == ' ') || (ch == '\t') || (ch == '\n'))
		ch = getchar();
	ch = toupper(ch);
	*temp = ch;
	int counter = 1;
	while ((ch = getchar()) != '\n' && counter < INGREDIENT_BUFFER_LEN){
		ch = tolower(ch);
		if (((ch == ' ') || (ch == '\t')) && (*(temp+counter-1) == ' '))
			continue;
		if (*(temp+counter-1) == ' ')
			ch = toupper(ch);
		*(temp+counter) = ch;
		counter++;
	}
	if (*(temp+counter) == ' ')
		*(temp+counter) = '\0';  
}

/************************************************************************************************************
* 																											*
*	  clearScreen prints an escape sequence to clear the terminal											*
*																											*
*************************************************************************************************************/
void clearScreen(void){
	printf("\033[2J\033[H"); // ANSI escape sequence to clear screen
}