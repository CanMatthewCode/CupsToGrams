#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"
#include "recipeLinkedList.h"
#include "recipeConversions.h"
#include "recipeSystemCheck.h"


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
	char openFileBuffer[PATH_MAX] = {'\0'};
	#ifdef _WIN32
		snprintf(openFileBuffer, sizeof(openFileBuffer), "%s\\recipeFiles\\recipes.txt", pathwayBuffer);
	#else
		snprintf(openFileBuffer, sizeof(openFileBuffer), "%s/recipeFiles/recipes.txt", pathwayBuffer);
	#endif
	if ((fp = fopen(openFileBuffer, "w+")) == NULL){
		printf("Unable to open recipes.txt file\n");
		return -1;
	}
	while (recipe){
	//dump the name, enum type, and number of ingredients
		int counter = 0;
		fprintf(fp, "%s\t%d\n%d", recipe->recipeName, recipe->recipeType, recipe->numberOfIngredients);
	//loop to dump each ingredient's name, user entered cups, and float value of entered value separated by new lines
		while (counter < recipe->numberOfIngredients){
			fprintf(fp, "\n%d\t%s\t%s\t%.2f", recipe->ingredients[counter].nonWeighedIngredientFlag, recipe->ingredients[counter].ingredientName, recipe->ingredients[counter].userCupsInput, recipe->ingredients[counter].ingredientGrams);
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
		fprintf(fp, "\n\a\n");
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
	char openFileBuffer[PATH_MAX] = {'\0'};
	#ifdef _WIN32
		snprintf(openFileBuffer, sizeof(openFileBuffer), "%s\\recipeFiles\\recipes.txt", pathwayBuffer);
	#else
		snprintf(openFileBuffer, sizeof(openFileBuffer), "%s/recipeFiles/recipes.txt", pathwayBuffer);
	#endif
	if((fp = fopen(openFileBuffer, "r+")) == NULL){//"./recipeFiles/recipes.txt"
		if((fp = fopen(openFileBuffer, "w+")) == NULL){//"./recipeFiles/recipes.txt"
			fp = NULL;
			return NULL;
		}
	}
	//functionality to populate a linked list from the "recipe.txt" file and return pointer to head
    int numNodes = 0;
    char ch;
	//scan for * characters, ++numNodes for each one found to find the number or stored recipes
    while ((ch = fgetc(fp)) != EOF){
    	if (ch == '\a')
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
    	for (int i = 0; i < newNode->numberOfIngredients; i++){
    		fscanf(fp, " %d", &newNode->ingredients[i].nonWeighedIngredientFlag);
			while ((ch = fgetc(fp)) != '\t')
				;
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
    	}
    	fscanf(fp, " \a\n");
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

/********************************************************************************************************************
* 																													*
*	 			add a new node into the recipeStruct linked-list alphabetically										*
*				returns pointer to head on success, NULL on failure													*
*																													*
*********************************************************************************************************************/
struct recipeStruct *placeRecipeStructNode(struct recipeStruct *recipeHead, struct recipeStruct *newRecipe){
	struct recipeStruct *cur = recipeHead;
	struct recipeStruct *prev = NULL;
	struct recipeStruct *newNode = newRecipe;

	//if cur == NULL it is the first node
	if (cur == NULL)
		return newNode;
	
	//if buffer is smaller than 1st node, it is new 1st node
	if ((cur != NULL) && (strcmp(newNode->recipeName, cur->recipeName) < 0)){
		newNode->next = cur;
		cur->prev = newNode;
		return newNode;
	}
	//loop to check the rest
	for ( ; cur->next != NULL && (strcmp(newNode->recipeName, cur->recipeName) > 0); prev = cur, cur = cur->next)
		;
	//final node case
	if ((strcmp(newNode->recipeName, cur->recipeName) > 0) && cur->next == NULL){
		newNode->prev = cur;
		cur->next = newNode;
	//if the list is 1 long and this is 2nd node added
		if (prev == NULL)
			return cur;
	}
	//all middle cases
	if ((strcmp(newNode->recipeName, prev->recipeName) > 0) && 
	   (strcmp(newNode->recipeName, cur->recipeName) < 0)){
		newNode->prev = prev;
		newNode->next = cur;
		prev->next = newNode;
		cur->prev = newNode;
	} 

	//resetting file pointer to head
	while (cur->prev != NULL)
		cur = cur->prev;
	return cur;
}

/********************************************************************************************************************
* 																													*
*	 			finds if a recipe name already exists in the recipe linked-list										*
*				returns pointer to the recipe on success, NULL on failure											*
*																													*
*********************************************************************************************************************/
struct recipeStruct *doesRecipeNameExist(struct recipeStruct *recipeHead, char buffer[INGREDIENT_BUFFER_LEN]){
	struct recipeStruct *cur = recipeHead;
//	struct recipeStruct *next = NULL;
	while (cur){
		if (strcmp(buffer, cur->recipeName) == 0)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

/********************************************************************************************************************
* 																													*
*	  			finds a recipe in the recipeStruct linked list by parsing a buffer to find comparable names			*
*				returns NULL if no recipe with a partially matching name is found									*
*																													*
*********************************************************************************************************************/
struct recipeStruct *findRecipe(struct recipeStruct *recipeHead, char buffer[INGREDIENT_BUFFER_LEN]){
	//create array of pointers to store possible found ingredients, make sure it is NULL to start
	struct recipeStruct *foundRecipes[MAX_INGREDIENTS_FOUND] = {NULL};
	memset(foundRecipes, 0, sizeof(foundRecipes));
	
	unsigned int recipeCounter = 0;
	unsigned int recipeChoice = 0;
	//iterate through all sub-lists from the head node of the ingredientType linked list searching for partial matches
	//store partial matches in array to share with user as well as their ingredientTypeNodes which store the matches' head pointers
	struct recipeStruct *possibleRecipe = NULL;
	//move through recipeStruct linked-list until NULL on searching for partial matches
	for (possibleRecipe = recipeHead; possibleRecipe != NULL; possibleRecipe = possibleRecipe->next){
			if (strstr(possibleRecipe->recipeName, buffer) != NULL)
				foundRecipes[recipeCounter++] = possibleRecipe;
	}
	if (recipeCounter == 0){
		printf("\n\n\t\tRecipe Not Found (Hit Enter To Continue)");
		char ch = '\0';
		while ((ch = getchar()) != '\n');
		return NULL;
	}
	if ((recipeCounter == 1) && (strcmp(foundRecipes[0]->recipeName, buffer) == 0))
		return foundRecipes[0];
	unsigned int i = 0;
	for (i = 1; i <= recipeCounter; i++)
		printf("\t\t%i) %s\n", i, foundRecipes[i-1]->recipeName);
	printf("\t\t%i) None Of The Above\n", i);
	while ((recipeChoice == 0) || ((recipeChoice <= 0) || (recipeChoice > (recipeCounter + 1)))){
        printf("\t\tEnter Recipe Number: ");
        recipeChoice = getNumericChoice();
	    if ((recipeChoice <= 0) || (recipeChoice > (recipeCounter + 1))){
	       		printf("\t\tInvalid Entry: ");
	       		while (getchar() != '\n');
	    }
    }
    //if none of the above are correct, return NULL
    if (recipeChoice == (recipeCounter + 1))
    	return NULL;

	return foundRecipes[recipeChoice - 1];
}

/**********************************************************************************************************v*********
* 																													*
*	 			delete recipe permanently from recipe linked-list													*
*				returns recipeType pointer to head on success, NULL on failure or cancel							*
*																													*
*********************************************************************************************************************/
struct recipeStruct *deleteFullRecipeNode(struct recipeStruct *recipeHead, struct recipeStruct *recipeToDelete){
	char confirm = '\0';
	struct recipeStruct *cur = recipeToDelete;
	struct recipeStruct *prev = NULL;
	struct recipeStruct *next = NULL;
	struct recipeStruct *headPointer = recipeHead;
	puts("\n\n\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	puts("\t\tx\t\t\t\t\t\t\t\t\t\tx");
	puts("\t\tx\t\t      -PERMANENTLY DELETE FULL REICPE- \t\t\t\tx");
	puts("\t\tx\t\t\t\t\t\t\t\t\t\tx");
	puts("\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	printf("\n\n\t\tConfirm PERMANENTLY DELETING \"%s\" Recipe In Full (y/n): ", recipeToDelete->recipeName);
	YESNOCHOICE(confirm);
	if (confirm == 'N')
		return recipeHead;
	if (headPointer == NULL){
		printf("\t\tRecipe List is Empty\n");
		return NULL;
	} 
	if (cur == NULL){
		printf("\t\tRecipe To Delete Is Empty\n");
		return NULL;
	}
	if (cur && headPointer){
		prev = cur->prev;
		next = cur->next;
	}
	//if it is the only node
	if ((!prev) && (!next)){
		headPointer = NULL;
	//if prev == NULL, it is the first node;
	} else if ((!prev) && (next)){
		headPointer = next;
		next->prev = NULL;
	//if it is a middle node	
	} else if ((prev) && (next)){
		prev->next = next;
		next->prev = prev;
	//if it is the final node
	} else if (prev && (!next))
		prev->next = NULL; 
	dumpRecipesFromLinkedList(headPointer);
	free(cur);
	return headPointer;
}

/********************************************************************************************************************
* 																													*
*	 			free full recipeStruct linked-list from memory														*
*																													*
*********************************************************************************************************************/
void freeRecipeStructList(struct recipeStruct *recipeHead){
	struct recipeStruct *cur = recipeHead;
	struct recipeStruct *temp;
	while (cur){
		temp = cur;
		cur = cur->next;
		free(temp);
	}
	temp = NULL;
}
