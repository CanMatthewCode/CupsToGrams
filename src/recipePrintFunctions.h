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
struct recipeStruct *printFullRecipeWithPDFOption(struct recipeStruct *recipe, struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

/********************************************************************************************************************
* 																													*
*	 			prints the names of all the nodes in the recipeStruct linked-list alphabetically					*
*																													*
*********************************************************************************************************************/
struct recipeStruct *printAllRecipeNames(struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

/********************************************************************************************************************
* 																													*
*	  			prints all recipe nodes of a chosen food type						 								*
*																													*
*********************************************************************************************************************/
struct recipeStruct *printRecipeByType (struct recipeStruct *recipeHead, struct ingredientType *ingredientHead);

#endif //RECIPEPRINTFUNCTIONS_H
