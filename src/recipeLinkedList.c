#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"
#include "recipeLinkedList.h"
#include "recipeConversions.h"

/*
	x. placeRecipeStructNode into linked list alphabetically
	x. deleteRecipe to delete a node from the linked list
	x. find recipes to find all recipes that have the user's input and display the options like the ingredients find function
	x. free recipeStruct linked list function
	x. print out all recipe names
	x. print recipe names by recipe type
*/
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
	if (strcmp(newNode->recipeName, cur->recipeName) == 0){
		printf("\n\t\tRecipe Already Exists\n");
		//have option here to change name instead of deleting
		free(newNode);
		newNode = NULL;
		return recipeHead;
	}
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

	if (strcmp(newNode->recipeName, cur->recipeName) == 0){
		printf("\n\t\tRecipe Already Exists\n");
		//have option here to change name instead of deleting
		free(newNode);
		newNode = NULL;
	}
	//resetting file pointer to head
	while (cur->prev != NULL)
		cur = cur->prev;
	return cur;
}

/********************************************************************************************************************
* 																													*
*	 			prints the names of all the nodes in the recipeStruct linked-list alphabetically					*
*																													*
*********************************************************************************************************************/
void printAllRecipeNames(struct recipeStruct *recipeHead){
	struct recipeStruct *cur = NULL;
	int counter = 0;
	clearScreen();
	puts("\n\n\t\t*********************************************************************************");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*\t\t\t  -ALL RECIPES AVAILABLE-       \t\t\t*");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*********************************************************************************\n\n");
	printf("\t\t");
	for (cur = recipeHead; cur; cur = cur->next){
		printf("%-32s", cur->recipeName);
		counter++;
		if (counter % 3 == 0)
			printf("\n\n\n\t\t");
	}
	printf("\n\n\t\tHit Enter To Continue\t");
	char ch = '\0';
	while ((ch = getchar()) != '\n');
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
	if (recipeCounter == 0)
		return NULL;
	if ((recipeCounter == 1) && (strcmp(foundRecipes[0]->recipeName, buffer) == 0))
		return foundRecipes[0];
	int i = 0;
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
    if (recipeChoice == (recipeChoice + 1))
    	return NULL;

	return foundRecipes[recipeChoice - 1];
}

/**********************************************************************************************************v*********
* 																													*
*	 			delete recipe permanently from recipe linked-list													*
*				returns recipeType pointer to head on success, NULL on failure or cancel							*
*																													*
*********************************************************************************************************************/
struct recipeStruct *deleteFullRecipeNode(struct recipeStruct *head, struct recipeStruct *recipeToDelete){
	char confirm = '\0';
	struct recipeStruct *cur = recipeToDelete;
	struct recipeStruct *prev = NULL;
	struct recipeStruct *next = NULL;
	struct recipeStruct *headPointer = head;
	puts("\n\n\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	puts("\t\tx\t\t\t\t\t\t\t\t\t\tx");
	puts("\t\tx\t\t      -PERMANENTLY DELETE FULL REICPE- \t\t\t\tx");
	puts("\t\tx\t\t\t\t\t\t\t\t\t\tx");
	puts("\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	printf("\n\n\t\tConfirm PERMANENTLY DELETING \"%s\" Recipe In Full (y/n): ", recipeToDelete->recipeName);
	YESNOCHOICE(confirm);
	if (confirm == 'N')
		return head;
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
	return headPointer;
}
/*
	if (cur && headPointer){
		prev = cur->prev;
		next = cur->next;
	//if prev == NULL, it is the 1st node
		if (!prev)
			headPointer = cur->next;
	//if it is a middle node
		else if (prev != NULL && next != NULL){
			prev->next=next;
			next->prev=prev;
		}
	//if it is the final node
		else if(prev && next == NULL)
			prev->next = NULL;
		free(cur);
		cur = NULL;
*/


/********************************************************************************************************************
* 																													*
*	  			prints all recipe nodes of a chosen food type						 								*
*																													*
*********************************************************************************************************************/
void printRecipeByType (struct recipeStruct *headPointer){
	struct recipeStruct *cur = headPointer;
	int counter = 0;
	clearScreen();
	puts("\n\n\t\t*********************************************************************************");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*\t\t\t  -SHOW RECIPE NAMES BY FOOD TYPE-       \t\t*");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*********************************************************************************\n\n");
	int choice = 0;
	puts("\n\n\t\t(1) APPETIZER\t\t(2) BAKED GOOD\t\t(3) BREAKFAST\t\t(4) DESSERT\n\n\t\t(5) LUNCH\t\t(6) ENTREE\t\t(7) SIDE DISH\t\t(8) SNACK\n\n\t\t(9)SOUP");
	printf("\n\n\t\tEnter Number(#) Of Food Type To Print: ");
	do {
		choice = getNumericChoice();
		if (choice < 1 || choice > 9)
			printf("\t\tInvalid Entry, Try Again: ");
	} while (choice < 1 || choice > 9);
	printf("\n\t\t");
	for ( ; cur; cur = cur->next){
		if (cur->recipeType == choice - 1){
			printf("%-32s", cur->recipeName);
			counter++;
			if (counter % 3 == 0)
				printf("\n\n\n\t\t");
		}
	}
	printf("\n\n\t\tHit Enter To Continue\t");
	char ch = '\0';
	while ((ch = getchar()) != '\n');
}

/********************************************************************************************************************
* 																													*
*	 			free full recipeStruct linked-list from memory														*
*																													*
*********************************************************************************************************************/
void freeRecipeStructList(struct recipeStruct *head){
	struct recipeStruct *cur = head;
	struct recipeStruct *temp;
	while (cur){
		temp = cur;
		cur = cur->next;
		free(temp);
	}
	temp = NULL;
}