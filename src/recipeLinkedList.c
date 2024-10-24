#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"
#include "recipeLinkedList.h"
#include "recipeConversions.h"

/********************************************************************************************************************
* 																													*
*	  			creates new recipeStruct node, returns NULL on failure				 								*
*																													*
*********************************************************************************************************************/
struct recipeStruct *createNewRecipeNode(void){
	struct recipeStruct *newRecipe = calloc(1, sizeof(struct recipeStruct));
	if (newRecipe == NULL){
		perror("Failure to allocate memory for newRecipe node");
		return NULL;
	}
	return newRecipe;
}

/********************************************************************************************************************
* 																													*
*	  			dumps all recipeStruct nodes to text files, returns 0 on success, -1 on failure						*
*																													*
*********************************************************************************************************************/
int dumpRecipesFromLinkedList(struct recipeStruct *recipeHead){
	FILE *fp = NULL;
	struct recipeStruct *recipe = recipeHead;
	if ((fp = fopen("./recipeFiles/recipes.txt", "w+")) == NULL){
		printf("Unable to open recipes.txt file\n");
		return -1;
	}
	while (recipe){
	//dump the name, enum type, and number of ingredients
		int counter = 0;
		fprintf(fp, "%s\t%d\n%d", recipe->recipeName, recipe->recipeType, recipe->numberOfIngredients);
	//loop to dump each ingredient's name, user entered cups, and float value of entered value separated by new lines
		while (counter < recipe->numberOfIngredients){
			fprintf(fp, "\n%s\t%s\t%.2f", recipe->ingredients[counter].ingredientName, recipe->ingredients[counter].userCupsInput, recipe->ingredients[counter].ingredientGrams);
			counter++;
		}
	//loop to dump each instruction, followed by two new lines to distinguish each instruction which may have its own internal new line character
		fprintf(fp, "\n%d\n", recipe->numberOfInstructions);
		counter = 0;
		while (counter < recipe->numberOfInstructions){
			fprintf(fp, "%s\n\n", recipe->recipeInstructions[counter]);
			counter++;
		}
	//loop to dump each note, followed by two new lines to distinguish each note which may have its own internal new line character
		fprintf(fp, "%d\n", recipe->numberOfNotes);
		counter = 0;
		while (counter < recipe->numberOfNotes){
			fprintf(fp, "%s\n\n", recipe->recipeNotes[counter]);
			counter++;
		}
	//print * character to distinguish between recipes and to scan later to get a count of number of recipes
		fprintf(fp, "\n*\n");
	//move on to the next recipe in the linked list alphabetically
		recipe = recipe->next;
	}
	fclose(fp);
	fp = NULL;
	return 0;
}

/********************************************************************************************************************
* 																													*
*	  			loadRecipes loads the recipes into a linked-list from a recipes.txt file							*
*				returns a pointer to recipe link-list head on success, NULL on failure								*
*																													*
*********************************************************************************************************************/
struct recipeStruct *loadRecipesToLinkedList(void){
	FILE *fp = NULL;
	struct recipeStruct *cur = NULL;
	//open linked list of ingredient types which each have their own linked list inside
	if((fp = fopen("./recipeFiles/recipes.txt", "r+")) == NULL){
		if((fp = fopen("./recipeFiles/recipes.txt", "w+")) == NULL){
			fp = NULL;
			return NULL;
		}
	}
	//functionality to populate a linked list from the "recipe.txt" file and return pointer to head
    int numNodes = 0;
    char ch;
	//scan for * characters, ++numNodes for each one found to find the number or stored recipes
    while ((ch = fgetc(fp)) != EOF){
    	if (ch == '*')
    		numNodes++;
    }
    if (numNodes == 0)
    	return NULL;
    rewind(fp);
    //loop to populate the link list from the text file
    for (int i = 0; i < numNodes; i++){
    	struct recipeStruct *newNode = NULL;
    	if ((newNode = createNewRecipeNode()) == NULL){
    		fprintf(stderr, "Unable to Create Recipe Node to Load List\n");
    		fp = NULL;
    		return NULL;
    	}
		int counter = 0;
	//loops to add each of the members from the text file - need to scan in same order as dumped
    //load name, enum type, number of ingredients
    	while ((ch = fgetc(fp)) != '\t')
    		newNode->recipeName[counter++] = ch;
    	fscanf(fp, " %u %d ", &newNode->recipeType, &newNode->numberOfIngredients);
    //loop to load each ingredient's name, user entered cups, and float value of entered value separated by new lines
    	for (int i = 0; i < newNode->numberOfIngredients; ++i){
    		int counter = 0;
    		while ((ch = fgetc(fp)) != '\t')
    			newNode->ingredients[i].ingredientName[counter++] = ch;
    		counter = 0;
    		while ((ch = fgetc(fp)) != '\t')
    			newNode->ingredients[i].userCupsInput[counter++] = ch;
    		fscanf(fp, " %f ", &newNode->ingredients[i].ingredientGrams);
    	}
    	
    	fscanf(fp, " %d ", &newNode->numberOfInstructions);
    //loop to load each instruction, use the two new lines to distinguish each instruction which may have its own internal new line character
		for (int i = 0; i < newNode->numberOfInstructions; i++){
			int counter = 0;
			while ((ch = fgetc(fp)) != EOF){
				if (counter > 0 && newNode->recipeInstructions[i][counter - 1] == '\n' && ch == '\n'){
					break;
				}else
					newNode->recipeInstructions[i][counter++] = ch;
			}
	//replace trailing new line character
			if (newNode->recipeInstructions[i][counter - 1] == '\n')
				newNode->recipeInstructions[i][counter - 1] = '\0';	
		}
    	
    	fscanf(fp, " %d ", &newNode->numberOfNotes);
    //loop to load each note, use the two new lines to distinguish each note which may have its own internal new line character
    	for (int i = 0; i < newNode->numberOfNotes; i++){
    		int counter = 0;
    		while ((ch = fgetc(fp)) != EOF){
    			if (counter > 0 && newNode->recipeNotes[i][counter - 1] == '\n' && ch == '\n'){
					break;
				}else
					newNode->recipeNotes[i][counter++] = ch;
			}
	//replace trailing new line character
			if (newNode->recipeNotes[i][counter - 1] == '\n')
				newNode->recipeNotes[i][counter - 1] = '\0';
		fscanf(fp, " *");	
    	}
    //place it at the end of the linked list since they are already sorted alphabetically prior to being dumped	
    //if cur is NULL this is the first node in the linked list and is therefore head, otherwise, link backwards
    	if (cur == NULL)
    		cur = newNode;
    	else {
    		cur->next = newNode;
    		newNode->prev = cur;
    		cur = newNode;
    	}
    }
    fclose(fp);
    fp = NULL;
    //resetting file pointer to head
    while (cur->prev != NULL)
    	cur = cur->prev;
    return cur;
}
