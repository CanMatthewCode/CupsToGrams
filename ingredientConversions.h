#ifndef INGREDIENTCONVERSIONS_H
#define INGREDIENTCONVERSIONS_H

#include <stdio.h>
#include <ctype.h>

#define INGREDIENT_BUFFER_LEN 30

struct ingredientItem{
	char ingredientName[INGREDIENT_BUFFER_LEN];
	float gramsPerCup;
	struct ingredientItem *next;	
};

struct ingredientType{
	char typeName[INGREDIENT_BUFFER_LEN];
	struct ingredientItem *head;
	struct ingredientType *next;
};

/************************************************************************************************************
* 																											*
*	  getCups Converts User Input in the form of Cups, Cups Part/Cups, or Cups.Parts to a float value		*
*																											*
*************************************************************************************************************/
float getCups(void);

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
 
#endif