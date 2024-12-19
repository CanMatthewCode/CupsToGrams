#ifndef RECIPEPRINTFUNCTIONS_H
#define RECIPEPRINTFUNCTIONS_H

#include "ingredientConversions.h"
#include "recipeConversions.h"

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
*	 			prints the names of all the nodes in the recipeStruct linked-list alphabetically					*
*																													*
*********************************************************************************************************************/
void printAllRecipeNames(struct recipeStruct *recipeHead);

/********************************************************************************************************************
* 																													*
*	  			prints all recipe nodes of a chosen food type						 								*
*																													*
*********************************************************************************************************************/
void printRecipeByType (struct recipeStruct *recipeHead);

#endif //RECIPEPRINTFUNCTIONS_H
