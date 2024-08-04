#ifndef CONVERTINGREDIENT_H
#define CONVERTINGREDIENT_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "ingredientMenus.h"
#include "ingredientTypeLinkedList.h"


/************************************************************************************************************
* 																											*
*				functionality for the ingredientType linked-list from the main menu option					*
*																											*
*************************************************************************************************************/
struct ingredientType *convertIngredientMenu(struct ingredientType *head);

/************************************************************************************************************
* 																											*
*				add a node to the ingredientType linked-list from the main menu option						*
*				returns pointer to head of list on success, NULL on failure									*
*																											*
*************************************************************************************************************/
struct ingredientType *addIngredientType(struct ingredientType *head);

/************************************************************************************************************
* 																											*
*				add a node to the ingredientItem linked-list from the convert ingredient menu				*
*				enter ingredient type to access linked-list type. returns pointer to head of list 			*
*																											*
*************************************************************************************************************/
void addIngredientItem(struct ingredientType *head);

/************************************************************************************************************
* 																											*
*				find any ingredient item node that matches partially with user input				 		*
*				if multiple options found, give options, then print chosen node								*
*																											*
*************************************************************************************************************/
void findIngredient(struct ingredientType *head);

/************************************************************************************************************
* 																											*
*				print all ingredient items from sub-list stored in an ingredientType node					*
*																											*
*************************************************************************************************************/
void printAllIngredientItemsInTypeNode(struct ingredientType *head);

/************************************************************************************************************
* 																											*
*				modify an ingredientItem node's name, weight, tablespoonFlag								*
*																											*
*************************************************************************************************************/
void modifyIngredientItem(struct ingredientType *head);

/************************************************************************************************************
* 																											*
*				delete an ingredientItem node permanently from an ingredientItem linked list				*
*																											*
*************************************************************************************************************/
void deleteIngredientItem (struct ingredientType *head);

#endif //CONVERTINGREDIENT_H