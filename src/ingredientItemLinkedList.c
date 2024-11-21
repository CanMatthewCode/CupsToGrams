#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"
#include "recipeSystemCheck.h"


/********************************************************************************************************************
* 																													*
*	  			create a new node memory block with calloc for an ingredientItem linked-list node		 			*
*				returns a pointer to the new memory block on success, NULL on failure								*
*																													*
*********************************************************************************************************************/
struct ingredientItem *createIngredientItemNode(void){
	struct ingredientItem *ingredientItemNode = calloc(1, sizeof(struct ingredientItem));
	if (ingredientItemNode == NULL){
		perror("Failure to allocate memory for ingredientItem node");
		return NULL;
	}
	return ingredientItemNode;
}

/************************************************************************************************************
* 																											*
*	  	loadIngredientItem loads the ingredientsItems linked-list associated with an ingredientType pointer *
*		loads a .txt file from the typeName buffer in the ingredientType struct								*
*		returns a pointer to ingredientItem link-list head on success, NULL on failure						*
*																											*
*************************************************************************************************************/
struct ingredientItem *loadIngredientItem(struct ingredientType *node){
	FILE *fp = NULL;
	struct ingredientType *ingredientType = node;
	struct ingredientItem *cur = NULL;

	char openFileBuffer[PATH_MAX] = {'\0'};
	#ifdef _WIN32
		snprintf(openFileBuffer, sizeof(openFileBuffer), "%s\\textFiles\\%s.txt", pathwayBuffer, ingredientType->typeName);
	#else
		snprintf(openFileBuffer, sizeof(openFileBuffer), "%s/textFiles/%s.txt", pathwayBuffer, ingredientType->typeName);
	#endif
	if ((fp = fopen(openFileBuffer, "r+")) == NULL){
		if ((fp = fopen(openFileBuffer, "w+")) == NULL)
			return NULL;
	}
	//functionality to populate a linked list from the "[IngredientName].txt" file and return pointer to head
    int numNodes = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF){
    	if (ch == '\n')
    		numNodes++;
    }
    if (numNodes == 0)
    	return NULL;
    rewind(fp);
	
	//loop to populate the link list from the text file
    for (int i = 0; i < numNodes; i++){
    	struct ingredientItem *newNode = NULL;
    	if ((newNode = createIngredientItemNode()) == NULL){
    	    fprintf(stderr, "Unable to Create Ingredient Item Node to Load List\n");
    		fp = NULL;
    		return NULL;
    	}
    	//print characters until you get to a new line
    	ch = '\0';
    	int position = 0;
    	while (((ch = fgetc(fp)) != '\t') && (position < (INGREDIENT_BUFFER_LEN - 1)))
    		newNode->ingredientName[position++] = ch;
    	if (ch == EOF){
    		fprintf(stderr, "Unable to populate Ingredient Items from %s\n", openFileBuffer);
    		free(newNode);
    		fclose(fp);
    		fp = NULL;
    		return NULL;
    	}
    	fscanf(fp, " %f", &newNode->gramsPerCup);
    	char flagBuffer[10] = {'\0'};  
		if (fscanf(fp, "%9[^\n]\n", flagBuffer) == 1) {
    		if (strcmp(flagBuffer, " g/tbsp") == 0)
    			newNode->tablespoonFlag = 1;
    	}
		//if cur is NULL it is the first node of the linked list and is therefore head, otherwise, link backwards
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
    //rewind file pointer to head
    while (cur->prev != NULL)
    	cur = cur->prev;
    return cur;
}

/************************************************************************************************************
* 																											*
*	  	loadIngredientItem loads the ingredientsItems linked-list associated with an ingredientType pointer *
*		loads a .txt file from the typeName buffer in the ingredientType struct								*
*		returns a pointer to ingredientItem link-list head on success, NULL on failure						*
*																											*
*************************************************************************************************************/
struct ingredientType *loadAllIngredientTypeSubLists(struct ingredientType *typeHead){
	struct ingredientType *cur = typeHead;
	struct ingredientType *prev = NULL;
	while (cur){
		cur->head = loadIngredientItem(cur);
		if (cur->head == NULL)
			printf("\t\t%s Ingredient List Empty or Failed to Load.  Check Text Files\n", cur->typeName);
		prev = cur;
		cur = cur->next;
	}
	while (prev->prev != NULL)
		prev = prev->prev;
	return prev;
}

/********************************************************************************************************************
* 																													*
*	 			dump the ingredient item names from linked-list into link ingredientTypes->typeName.txt file		*
*				returns -1 on failure to open IngredientTypes.txt file, return 0 on successful dump					*
*																													*
*********************************************************************************************************************/
int dumpIngredientItemList(struct ingredientType *typeNode){
	FILE *fp = NULL;
	struct ingredientType *ingredientTypeNode = typeNode;
	char openFileBuffer[PATH_MAX] = {'\0'};
	#ifdef _WIN32
		snprintf(openFileBuffer, sizeof(openFileBuffer), "%s\\textFiles\\%s.txt", pathwayBuffer, ingredientTypeNode->typeName);
	#else
		snprintf(openFileBuffer, sizeof(openFileBuffer), "%s/textFiles/%s.txt", pathwayBuffer, ingredientTypeNode->typeName);
	#endif
	if ((fp = fopen(openFileBuffer, "w+")) == NULL){
		printf("Unable to open %s file\n", openFileBuffer);
		return -1;
	}
	//head for ingredientItem of each ingredientType is attached to the ingredientType node
	struct ingredientItem *cur = ingredientTypeNode->head;
	while (cur){
		fprintf(fp, "%s\t%f", cur->ingredientName, cur->gramsPerCup);
		if (cur->tablespoonFlag == 1)
			fprintf(fp, " g/tbsp\n");
		else 
			fprintf(fp, " g/cup\n");
		cur = cur->next;
	}
	fclose(fp);
	fp = NULL;
	return 0;
}

/********************************************************************************************************************
* 																													*
*	 			check user input key against existing ingredientItem lists											*
*				accepts an ingredientType pointer as a 3rd argument to allow an out parameter when the matches'		*
*				head node is needed. Enter NULL as 3rd parameter if ingredientType pointer is not wanted 			*
*				returns pointer to ingredientItem node found on success, NULL on failure							*
*																													*
*********************************************************************************************************************/
//enter NULL if out parameter is not needed - have a check in the find code to make sure it is not NULL before use
struct ingredientItem *findIngredientItemNode(struct ingredientType *head, char buffer[INGREDIENT_BUFFER_LEN], struct ingredientType **ingredientTypeNode){
	//create array of pointers to store possible found ingredients, make sure it is NULL to start
	struct ingredientItem *foundIngredients[MAX_INGREDIENTS_FOUND] = {NULL};
	memset(foundIngredients, 0, sizeof(foundIngredients));
	//create a pointer array for ingredientTypes that match the found ingredientItems so it can pass out an ingredientType pointer for the dumpIngredientItemList function
	struct ingredientType *foundIngredientsTypes[MAX_INGREDIENTS_FOUND] = {NULL};
	memset(foundIngredientsTypes, 0, sizeof(foundIngredientsTypes));
	
	unsigned int ingredientItemCounter = 0;
	unsigned int ingredientItemChoice = 0;
	//iterate through all sub-lists from the head node of the ingredientType linked list searching for partial matches
	//store partial matches in array to share with user as well as their ingredientTypeNodes which store the matches' head pointers
	struct ingredientType *ingredientTypePointer = NULL;
	struct ingredientItem *possibleItem = NULL;
	//move through ingredientType linked-list and sub-lists one by one until NULL on both searching for partial matches
	for (ingredientTypePointer = head; ingredientTypePointer != NULL; ingredientTypePointer=ingredientTypePointer->next){
		for (possibleItem = ingredientTypePointer->head; possibleItem != NULL; possibleItem = possibleItem->next){
			if (strstr(possibleItem->ingredientName, buffer) != NULL){
				foundIngredients[ingredientItemCounter] = possibleItem;
				foundIngredientsTypes[ingredientItemCounter++] = ingredientTypePointer;
			}
		}
	}
	if (ingredientItemCounter == 0)
		return NULL;
	if ((ingredientItemCounter == 1) && (strcmp(foundIngredients[0]->ingredientName, buffer) == 0)){
		if (ingredientTypeNode)
			*ingredientTypeNode = foundIngredientsTypes[0];
		return foundIngredients[0];
	}
	int i = 0;
	for (i = 1; i <= ingredientItemCounter; i++)
		printf("\t\t%i) %s\n", i, foundIngredients[i-1]->ingredientName);
	printf("\t\t%i) None Of The Above\n", i);
	while ((ingredientItemChoice == 0) || ((ingredientItemChoice <= 0) || (ingredientItemChoice > (ingredientItemCounter + 1)))){
        printf("\t\tEnter Ingredient Number: ");
        ingredientItemChoice = getNumericChoice();
	    if ((ingredientItemChoice <= 0) || (ingredientItemChoice > (ingredientItemCounter + 1))){
	       		printf("\t\tInvalid Entry: ");
	       		while (getchar() != '\n');
	    }
    }
    //if none of the above are correct, return NULL
    if (ingredientItemChoice == (ingredientItemCounter + 1))
    	return NULL;
    if (ingredientTypeNode)
    	*ingredientTypeNode = foundIngredientsTypes[ingredientItemChoice - 1];
	return foundIngredients[ingredientItemChoice - 1];
}

/********************************************************************************************************************
* 																													*
*	 			add a new node into the ingredientItem linked-list alphabetically									*
*				returns pointer to head on success, NULL on failure													*
*																													*
*********************************************************************************************************************/
struct ingredientItem *addNewIngredientItemNode(char buffer[INGREDIENT_BUFFER_LEN]){
	struct ingredientItem *newNode = NULL;
	newNode = createIngredientItemNode();
	strcpy(newNode->ingredientName, buffer);
	//functionality and safety for invalid entry on weight
	float gramsPerCup = 0.00;
    while (gramsPerCup == 0.00){
        printf("\t\tEnter Ingredient Weight In Grams: ");
	    if (scanf(" %f", &gramsPerCup) != 1){
	        printf("\t\tInvalid Entry\n");
	        while (getchar() != '\n');
	    }
	newNode->gramsPerCup = gramsPerCup;
    }
    while (getchar () != '\n');
	//enter functionality to populate ingredientItem->gramsPerCup and set tablespoonFlag
	printf("\t\tEnter Measurement Type (cups/tbsp): ");
  	char ch = '\0';
    do {
    	ch = '\0';
		ch = toupper(getchar());
		switch (ch){
			case 'C': 	break;
			case 'T': 	newNode->tablespoonFlag = 1;
						break;
			default:	printf("\t\tInvalid Selection, Try Again: ");
		}
		while (getchar () != '\n');
	} while ((ch != 'C') && (ch != 'T'));
	return newNode;
}

/********************************************************************************************************************
* 																													*
*	 			puts an ingredientItem node into the ingredientItem linked-list alphabetically						*
*																													*
*********************************************************************************************************************/
void placeIngredientItemNode(struct ingredientItem *ingredientItemNodeToAdd, struct ingredientType *nodeToAddsIngredientTypeNode){
	struct ingredientItem *cur = nodeToAddsIngredientTypeNode->head;
	struct ingredientItem *prev = NULL;
	struct ingredientItem *newNode = ingredientItemNodeToAdd;

	//if cur == NULL, it is the first node
	if (cur == NULL){
		nodeToAddsIngredientTypeNode->head = newNode;
		return;
	}
	//if buffer is smaller than 1st node, it is the new 1st node
	if ((cur != NULL) && (strcmp(newNode->ingredientName, cur->ingredientName) < 0)){
		newNode->next = cur;
		cur->prev = newNode;
		nodeToAddsIngredientTypeNode->head = newNode;
		return;
	}
	for ( ; cur->next != NULL && (strcmp(newNode->ingredientName, cur->ingredientName) > 0); prev = cur, cur = cur->next)
		;
	//final node case
	if ((strcmp(newNode->ingredientName, cur->ingredientName) > 0) && cur->next == NULL){
		newNode->prev = cur;
		cur->next = newNode;
		//if the list is 1 long and this is 2nd node added
		if (prev == NULL){
			nodeToAddsIngredientTypeNode->head = cur;
			return;
		}
			
	}
	//all middle cases
	if ((strcmp(newNode->ingredientName, prev->ingredientName) > 0) &&
		(strcmp(newNode->ingredientName, cur->ingredientName) < 0)){
			newNode->prev = prev;
			newNode->next = cur;
			prev->next = newNode;
			cur->prev = newNode;
	}
	if (strcmp(newNode->ingredientName, cur->ingredientName) == 0){
		printf("Ingredient Already Exists\n");
		free(newNode);
		newNode = NULL;
	}
	//resetting file pointer to head
	while (cur->prev != NULL)
		cur = cur->prev;
	nodeToAddsIngredientTypeNode->head = cur;
}

/********************************************************************************************************************
* 																													*
*	 			modifies the ingredientName in an existing ingredientType node in the linked-list 					*
*																													*
*********************************************************************************************************************/
void modifyIngredientItemNodeName(struct ingredientItem *nodeToModify, struct ingredientType *nodeToModifysIngredientTypeNode){
	struct ingredientItem *changedNode = nodeToModify;
	struct ingredientItem *prev = nodeToModify->prev;
	struct ingredientItem *next = nodeToModify->next;
	char choice = '\0';
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	while (choice != 'Y'){
		printf("\n\t\tEnter New Ingredient Name: ");
		memset(buffer, 0, sizeof(buffer));
		readUserInputIntoBuffer(buffer);
		printf("\n\t\tYou Entered: '%s', Is This Correct (y/n)?: ", buffer);
		YESNOCHOICE(choice);
	}
	if (choice == 'Y')
		strcpy(changedNode->ingredientName, buffer);
//if it is still in the right place alphabetically:
	if (((prev && next) && ((strcmp(changedNode->ingredientName, prev->ingredientName) > 0) && (strcmp(changedNode->ingredientName, next->ingredientName) < 0)))
		|| ((!prev && next) && (strcmp(changedNode->ingredientName, next->ingredientName) < 0)) || ((prev && !next) && (strcmp(changedNode->ingredientName, prev->ingredientName) > 0))){
		return;
	//if not and it is the first node: 
	} else {
		changedNode->prev = NULL;
		changedNode->next = NULL;
	 	if (!prev && next){
			nodeToModifysIngredientTypeNode->head = next;
			next->prev = NULL;
		//if it is a middle node:
		} else if (prev && next){
			prev->next = next;
			next->prev = prev;
		//if it is the final node:
		} else if (prev && !next){
			prev->next = NULL;
		}
	}
	placeIngredientItemNode(changedNode, nodeToModifysIngredientTypeNode);	
}

/********************************************************************************************************************
* 																													*
*	 			modifies the cupsPerGram amount in an existing ingredientType node in the linked-list 				*
*																													*
*********************************************************************************************************************/
void modifyIngredientItemNodeWeight(struct ingredientItem *nodeToModify){
	struct ingredientItem *changedNode = nodeToModify;
	char choice = '\0';
	float gramsPerCup = 0.00;
	while (choice != 'Y'){	
		gramsPerCup = 0.00;
		while (gramsPerCup == 0.00){
			printf("\n\t\tEnter New Ingredient Weight In Grams: ");
	    	if (scanf(" %f ", &gramsPerCup) != 1){
	       	 	printf("\t\tInvalid Entry");
	        	while (getchar() != '\n');
	           }
	       }
	    while (getchar() != '\n');
	    printf("\n\t\tYou Entered: '%.3f Grams', Is This Correct (y/n)?: ", gramsPerCup);
	    YESNOCHOICE(choice);
    }
    changedNode->gramsPerCup = gramsPerCup;
}

/********************************************************************************************************************
* 																													*
*	 			modifies the tablespoonFlag in an existing ingredientType node in the linked-list 					*
*																													*
*********************************************************************************************************************/
void modifyIngredientItemNodeFlag(struct ingredientItem *nodeToModify){
	struct ingredientItem *changedNode = nodeToModify;
	char choice = '\0';
	char measurementType = '\0';
	while (choice != 'Y'){
		printf("\n\t\tEnter Measurement Type (cups/tbsp): ");
		measurementType = '\0';
		while ((measurementType != 'C') && (measurementType != 'T')){
			measurementType = toupper(getchar());
			switch (measurementType){
			    case 'C': 	break;
				case 'T': 	break;
				default:	printf("\t\tInvalid Entry, Try Again: ");
			   	  		   	while (getchar() != '\n');
			}
		}
		while ((getchar()) != '\n');
		printf("\n\t\tYou Entered: \"");
		printf((measurementType == 'T') ? "g/tbsp" : "g/cups");
		printf("\", Is This Correct (y/n)?: ");
		YESNOCHOICE(choice);
	}
	//store choice of Tablespoon or Cup in the node's tablespoonFlag member
	changedNode->tablespoonFlag = (measurementType == 'T') ? 1 : 0;
}

/********************************************************************************************************************
* 																													*
*	 			print the information stored in an ingredientItem node 				 								*
*																													*
*********************************************************************************************************************/
void printIngredientItemNode(struct ingredientItem *node){
	printf("\t\t\t\t%-s:", node->ingredientName);
	int spaceCounter = (26 - strlen(node->ingredientName));
	for (int i = 0; i < spaceCounter; i++)
		printf(" ");
	printf("%6.2f ", node->gramsPerCup);
	printf(node->tablespoonFlag == 1 ? "g/tbsp" : "g/cup");
}

/********************************************************************************************************************
* 																													*
*	 			prints all the ingredientItem nodes stored in the head member of an ingredientType node 			*
*																													*
*********************************************************************************************************************/
void printAllIngredientItemNodes(struct ingredientType *node){
	struct ingredientType *typePointer = node;
	struct ingredientItem *itemPointer = typePointer->head;
	char ch = '\0';
	int i = 0;
	int spaceCounter = (38 - (strlen(node->typeName) / 2));
	printf("\n\n\t\t");
	for (int c = 0; c < spaceCounter; c++)
		printf(" ");
	while (typePointer->typeName[i] != '\0'){
		ch = typePointer->typeName[i++];
		printf("%c", toupper(ch));
	}
	printf("\n\n");
	while (itemPointer){
		printIngredientItemNode(itemPointer);
		printf("\n");
		itemPointer = itemPointer->next;
	}
}

/********************************************************************************************************************
* 																													*
*	 			delete an ingredientItem node						 				 								*
*				accepts the ingredientItem node to be deleted and it's attached ingredientType node as parameters	*
*				returns 0 on success, 1 on cancel													*
*																													*
*********************************************************************************************************************/
int deleteIngredientItemNode(struct ingredientItem *node, struct ingredientType *headNode){
	char choice = '\0';
	printf("\n\t\t%s Found, Confirm DELETE (y/n): ", node->ingredientName);
	YESNOCHOICE(choice);
	if (choice == 'N')
		return 1;	
	//delete functionality
	struct ingredientItem *cur = NULL;
	struct ingredientItem *next = NULL;
	struct ingredientItem *prev = NULL;
	
	cur = node;
	next = cur->next;
	prev = cur->prev;
	//if it is the only node
	if ((!prev) && (!next)){
		headNode->head = NULL;
	//if prev == NULL, it is the first node;
	} else if ((!prev) && (next)){
		headNode->head = next;
		next->prev = NULL;
	//if it is a middle node	
	} else if ((prev) && (next)){
		prev->next = next;
		next->prev = prev;
	//if it is the final node
	} else if (prev && (!next))
		prev->next = NULL;
		
	//reset to head and reattach head to the ingredientType's head member;
	if (prev){
		while (prev->prev != NULL)
			prev = prev->prev;
		headNode->head = prev;
	}
	//dump changed ingredientItem linked list to .txt file
	free(cur);
	cur = NULL;
	dumpIngredientItemList(headNode);
	return 0;
}

/********************************************************************************************************************
* 																													*
*	 			moves through the ingredientType linked list freeing all attached									*
*				ingredientItem linked lists from memory and setting the ingredientType member to NULL				*
*																													*
*********************************************************************************************************************/
void freeIngredientItemList(struct ingredientType *head){
	struct ingredientType *typeNode = head;
	struct ingredientItem *itemNode = NULL;
	struct ingredientItem *tempItemNode = NULL;
	while (typeNode){
		itemNode = typeNode->head;
		while (itemNode){
			tempItemNode = itemNode;
			itemNode = itemNode->next;
			free(tempItemNode);
		}
		typeNode->head = NULL;
		typeNode = typeNode->next;
	}
}
