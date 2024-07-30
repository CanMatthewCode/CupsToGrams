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

#endif //CONVERTINGREDIENT_H