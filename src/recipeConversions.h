#ifndef RECIPECONVERSIONS_H
#define RECIPECONVERSIONS_H

#include "ingredientConversions.h"
#include "pdfgen.h"
#define MAX_INGREDIENT_NUMBER 60
#define MAX_INGREDIENT_TEXT 1000
#define SCREEN_SIZE 65

#define TOTAL_VERTICAL_POINTS 792
#define TOTAL_HORIZONTAL_POINTS 612
#define V_FONT_POINTS 12
#define H_FONT_POINTS (V_FONT_POINTS / 2)
#define SIDE_MARGIN 60
#define TOP_BOTTOM_MARGIN 60
#define TOP_OF_PAGE_LINE 720
#define BOTTOM_OF_PAGE_LINE 60
#define SPACE_POINTS 5

enum recipeType{
	APPETIZER,
	BAKED_GOOD,
	BREAKFAST,
	DESSERT,
	LUNCH,
	ENTREE,
	SIDE,
	SNACK,
	SOUP
};

struct ingredientStruct{
	char ingredientName[INGREDIENT_BUFFER_LEN];
	char userCupsInput[INGREDIENT_BUFFER_LEN];
	float ingredientGrams;
	int nonWeightedIngredientFlag;
};

struct recipeStruct{
	char recipeName [INGREDIENT_BUFFER_LEN];
	int numberOfIngredients;
	struct ingredientStruct ingredients[MAX_INGREDIENT_NUMBER];
	int numberOfInstructions;
	char recipeInstructions [MAX_INGREDIENT_NUMBER][MAX_INGREDIENT_TEXT];
	int numberOfNotes;
	char recipeNotes [MAX_INGREDIENT_NUMBER][MAX_INGREDIENT_TEXT];
	enum recipeType recipeType;
	struct recipeStruct *prev;
	struct recipeStruct *next;
};

/********************************************************************************************************************
* 																													*
*				menu for adding new recipe functions, returns pointer to newly added recipe							*
*																													*
*********************************************************************************************************************/
struct recipeStruct *convertNewRecipe(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

/********************************************************************************************************************
* 																													*
*	  			add new ingredientStruct into currentRecipe struct. increases numberOfIngredients on success		*
*																													*
*********************************************************************************************************************/
void addNewIngredient(struct recipeStruct *currentRecipe, struct ingredientType *head);

/********************************************************************************************************************
* 																													*
*	  			add a new unmeasured ingredient into an ingredientStruct in currentRecipe struct. 					*
*				increases numberOfIngredients on success															*
*																													*
*********************************************************************************************************************/
void addNewNonMeasuredIngredient(struct recipeStruct *currentRecipe);

/********************************************************************************************************************
* 																													*
*	  			add new instruction into recipeStruct. increases numberOfInstruction on success						*
*																													*
*********************************************************************************************************************/
void addNewInstruction(struct recipeStruct *currentRecipe);

/********************************************************************************************************************
* 																													*
*	  			add new note into recipeStruct. Increases numberOfNotes on success									*
*																													*
*********************************************************************************************************************/
void addNewNote(struct recipeStruct *currentRecipe);

/********************************************************************************************************************
* 																													*
*	  			set enum recipeType type to: 	APPETIZER, BAKED_GOOD, BREAKFAST, DESSERT, MAINS,					*
*												SIDES, SNACKS, SOUPS.  												*
*				return 1 on success 0 on failure																	*
*																													*
*********************************************************************************************************************/
void setRecipeType(struct recipeStruct *currentRecipe);

/********************************************************************************************************************
* 																													*
*	  			used to fill in a recipeDirection or recipeNote field of a recipeStruct								*
*				returns the number of succesfull characters placed into the directionsBuffer						*
*																													*
********************************************************************************************************************/
int readUserInputIntoRecipe(char directionsBuffer[MAX_INGREDIENT_TEXT]);

/********************************************************************************************************************
* 																													*
*	  			prints a recipe's name surrounded by *** on top, bottom, and sides									*
*																													*
*********************************************************************************************************************/
void printRecipeName(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			prints a recipeStruct's ingredients in a listed order												*
*																													*
*********************************************************************************************************************/
void printRecipeIngredients(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			prints a recipeStruct's instructions in a listed order												*
*																													*
*********************************************************************************************************************/
void printRecipeInstructions(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			prints a recipeStruct's notes in a listed order														*
*																													*
*********************************************************************************************************************/
void printRecipeNotes(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*			  	prints a recipeStruct's recipeType enum as a string													*
*																													*
*********************************************************************************************************************/
void printRecipeType(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			prints the entirety of a recipeStruct's contents in a recipe-like manor								*
*																													*
*********************************************************************************************************************/
void printFullRecipe(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	 		 	prints the entirety of a recipeStruct's contents in a recipe-like manor								*
*				with the option to print the recipe to PDF															*
*																													*
*********************************************************************************************************************/
void printFullRecipeWithPDFOption(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			modifies the recipe's name in a recipeStruct, returns a pointer to recipeStruct head				*
*				for when recipe name change moves position in linked list											*
*																													*
*********************************************************************************************************************/
struct recipeStruct *modifyRecipeName(struct recipeStruct *recipeHead, struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			modifies the amount of an ingredient in a recipeStruct's ingredient's array							*
*																													*
*********************************************************************************************************************/
void modifyIngredientAmount(struct recipeStruct *recipe, struct ingredientType *ingredientHead);

/********************************************************************************************************************
* 																													*
*	  			reorders the ingredients in a recipeStruct's ingredient's array										*
*																													*
*********************************************************************************************************************/
void modifyIngredientOrder(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			deletes an ingredients from a recipeStruct's ingredients array										*
*																													*
*********************************************************************************************************************/
void deleteIngredientFromRecipe(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			modifies an instruction in a recipeStruct's instructions array										*
*																													*
*********************************************************************************************************************/
void modifyInstruction(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			reorders the instructions in a recipeStruct's instructions array									*
*																													*
*********************************************************************************************************************/
void modifyInstructionOrder(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			deletes an instruction from a recipeStruct's instructions array										*
*																													*
*********************************************************************************************************************/
void deleteInstructionFromRecipe(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			modifies an instruction in a recipeStruct's notes array												*
*																													*
*********************************************************************************************************************/
void modifyNote(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			reorders the notes in a recipeStruct's notes array													*
*																													*
*********************************************************************************************************************/
void modifyNoteOrder(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			deletes a note in a recipeStruct's notes array														*
*																													*
*********************************************************************************************************************/
void deleteNoteFromRecipe(struct recipeStruct *recipe);

/********************************************************************************************************************
* 																													*
*	  			accepts a recipeInstructions or recipeNotes formatted buffer and a buffer to store the PDF text		*
*				and returns the number of characters successfully copied into the PDF format buffer					*
*																													*
*********************************************************************************************************************/
int recipeBufferToPDFOutput (char *recipeToPDFBuffer, char *recipeNodeText);

/********************************************************************************************************************
* 																													*
*	  			saves a recipe to as a pdf document in a visually pleasing uniform style							*
*																													*
*********************************************************************************************************************/
void printRecipeToPDF(struct recipeStruct *recipeToPrint);

/********************************************************************************************************************
* 																													*
*	  			prints the recipe name in a star-box at the PDF's top and recipe type at the bottom					*
*				advances the linePointCounter by the number of PDF lines used by the recipe name box				*
*																													*
*********************************************************************************************************************/
void printRecipeNameAndTypeToPDF(struct pdf_doc *pdf, struct recipeStruct *recipeToPrint, int *linePointCounter);

/********************************************************************************************************************
* 																													*
*	  			adds a new page to the pdf with the recipe name in a star-box at the PDF's top and					*
*				recipe type at the bottom, resets linePointCounter to the total minus lines used for the box		*
*																													*
*********************************************************************************************************************/
void addNewPDFPage(struct pdf_doc *pdf, struct recipeStruct *recipeToPrint, int *linePointCounter);

#endif //RECIPECONVERSIONS_H
