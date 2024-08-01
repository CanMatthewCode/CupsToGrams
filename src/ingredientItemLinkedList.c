#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"

/*		XLoad from text file sub-ingredientItemLinkedList for each opened ingredientTypeNode->typeName.txt
*		XCheck if wanted ingredientType exists already in node
*		XCreate new node for ingredientTypeLinkedList
*		XPopulate and Add new node to ingredientItemLinkedList
*		XDelete selected node
*		XPrint ingredient node list
*		XDump ingredientTypeLinkedList into text file named ingredientType->ingredientName
*		Print All Ingredients by Type ~pretty~
*		freeIngredientTypeLinkedList function
*		freeAllIngredientTypeLinkedLists function
*/

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

	char openFileBuffer[INGREDIENT_BUFFER_LEN+15] = {'\0'};
	//add path to fopen() variable in openFileBuffer
	strcpy(openFileBuffer, "./textFiles/");
	//copy name from struct IngredientType node into openFileBuffer
	strcat(openFileBuffer, ingredientType->typeName);
	//append .txt to ingredientType names
	strcat(openFileBuffer, ".txt");
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
struct ingredientType *loadAllIngredientTypeSubLists(struct ingredientType *head){
	struct ingredientType *cur = head;
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

	char openFileBuffer[INGREDIENT_BUFFER_LEN+15] ={'\0'};
	//add path to fopen() variable in openFileBuffer
	strcpy(openFileBuffer, "./textFiles/");
	//copy name from struct IngredientType node into openFileBuffer
	strcat(openFileBuffer, ingredientTypeNode->typeName);
	//append .txt to ingredientType names
	strcat(openFileBuffer, ".txt");

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
*				returns pointer to node found on success, NULL on failure											*
*																													*
*********************************************************************************************************************/
struct ingredientItem *findIngredientItemNode(struct ingredientType *head, char buffer[INGREDIENT_BUFFER_LEN]){
	//create array of pointers to store possible found ingredients, make sure it is NULL to start
	struct ingredientItem *foundIngredients[MAX_INGREDIENTS_FOUND] = {NULL};
	memset(foundIngredients, 0, sizeof(foundIngredients));
	int ingredientItemCounter = 0;
	int ingredientItemChoice = 0;
	//iterate through all sub-lists from the head node of the ingredientType linked list searching for partial matches
	//store partial matches in array to share with user
	struct ingredientType *ingredientTypePointer = NULL;
	struct ingredientItem *possibleItem = NULL;
	//move through ingredientType linked-list and sub-lists one by one until NULL on both searching for partial matches
	for (ingredientTypePointer = head; ingredientTypePointer != NULL; ingredientTypePointer=ingredientTypePointer->next){
		for (possibleItem = ingredientTypePointer->head; possibleItem != NULL; possibleItem = possibleItem->next){
			if (strstr(possibleItem->ingredientName, buffer) != NULL)
				foundIngredients[ingredientItemCounter++] = possibleItem;
		}
	}
	if (ingredientItemCounter == 0){
		//printf("%s Not Found\n", buffer);
		return NULL;
	}
	if (ingredientItemCounter == 1)
		return foundIngredients[0];
	else if (ingredientItemCounter > 1){
		int i = 0;
		for (i = 1; i <= ingredientItemCounter; i++)
			printf("\t\t%i) %s\n", i, foundIngredients[i-1]->ingredientName);
		//add option that is 1 more than #of choices to be none of the above, exit without choosing
		printf("\t\t%i) None Of The Above\n", i);
		while ((ingredientItemChoice == 0) || ((ingredientItemChoice <= 0) || (ingredientItemChoice > (ingredientItemCounter + 1)))){
        	printf("\t\tEnter Ingredient Number: ");
	   		if ((scanf(" %i", &ingredientItemChoice) != 1) || 
	       	   ((ingredientItemChoice <= 0) || (ingredientItemChoice > (ingredientItemCounter + 1)))){
	       			printf("\t\tInvalid Entry\n");
	       			while (getchar() != '\n');
	    	}
    	}
    }
    //if none of the above are correct, return NULL
    if (ingredientItemChoice == (ingredientItemCounter + 1)){
    	while (getchar() != '\n');
    	return NULL;
    }
	return foundIngredients[ingredientItemChoice - 1];
}

/********************************************************************************************************************
* 																													*
*	 			add a new node into the ingredientItem linked-list alphabetically									*
*				returns pointer to head on success, NULL on failure													*
*																													*
*********************************************************************************************************************/
struct ingredientItem *addNewIngredientItemNode(struct ingredientItem *head, char buffer[INGREDIENT_BUFFER_LEN]){
	struct ingredientItem *cur = head;
	struct ingredientItem *prev = NULL;
	struct ingredientItem *newNode = NULL;
	
	newNode = createIngredientItemNode();
	strcpy(newNode->ingredientName, buffer);
	//enter functionality to populate ingredientItem->gramsPerCup and set tablespoonFlag
	printf("\t\tEnter Measurement Type (cups/tbsp): ");
  	char ch = '\0';
    while ((ch != 'C') && (ch != 'T')){
		ch = toupper(getchar());
		while (getchar() != '\n');
		switch (ch){
			case 'C': 	break;
			case 'T': 	newNode->tablespoonFlag = 1;
						break;
			default:	printf("\t\tInvalid Selection, Try Again: ");
		}
	}
	//safety for invalid entry on weight
	float gramsPerCup = 0.00;
    while (gramsPerCup == 0.00){
        printf("\t\tEnter Ingredient Weight In Grams: ");
	    if (scanf(" %f", &gramsPerCup) != 1){
	        printf("\t\tInvalid Entry\n");
	        while (getchar() != '\n');
	    }
	printf("\t\tCheck 0");
	newNode->gramsPerCup = gramsPerCup;
    }

	//if cur == NULL, it is the first node
	if (cur == NULL)
		return newNode;
	printf("\t\tCheck 1");
	//if buffer is smaller than 1st node, it is the new 1st node
	if ((cur != NULL) && (strcmp(newNode->ingredientName, cur->ingredientName) < 0)){
		newNode->next = cur;
		cur->prev = newNode;
		return newNode;
	}
	printf("\t\tCheck 2");
	for ( ; cur->next != NULL && (strcmp(newNode->ingredientName, cur->ingredientName) > 0); prev = cur, cur = cur->next)
		;
	//final node case
	if ((strcmp(newNode->ingredientName, cur->ingredientName) > 0) && cur->next == NULL){
		newNode->prev = cur;
		cur->next = newNode;
	//if the list is 1 long and this is 2nd node added
		if (prev == NULL)
			return cur;
	}
	printf("\t\tCheck 3");
	//all middle cases
	if ((strcmp(newNode->ingredientName, prev->ingredientName) > 0) &&
		(strcmp(newNode->ingredientName, cur->ingredientName) < 0)){
			newNode->prev = prev;
			newNode->next = cur;
			prev->next = newNode;
			cur->prev = newNode;
	}
	printf("\t\tCheck 4");

	if (strcmp(newNode->ingredientName, cur->ingredientName) == 0){
		printf("Ingredient Already Exists\n");
		free(newNode);
		newNode = NULL;
	}
	printf("\t\tCheck 5");
	//resetting file pointer to head
	while (cur->prev != NULL)
		cur = cur->prev;
	return cur;
}

/********************************************************************************************************************
* 																													*
*	 			modifies the ingredientName in an existing ingredientType node in the linked-list 					*
*																													*
*********************************************************************************************************************/
void modifyIngredientItemNodeName(struct ingredientItem *node){
	struct ingredientItem *changedNode = node;
	char ch = '\0';
	printIngredientItemNode(changedNode);
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	while (ch != 'Y'){
		printf("\n\t\tEnter New Ingredient Name: ");
		memset(buffer, 0, sizeof(buffer));
		readUserInputIntoBuffer(buffer);
		printf("\n\t\tYou Entered: '%s', Is This Correct (y/n)?: ", buffer);
		ch = getchar();
		ch = toupper(ch);
		while ((ch != 'Y') && (ch != 'N')){
			switch (ch) {
				case 'Y' : break;
				case 'N' : break;
				default  : printf("\n\t\tInvalid Selection, Try Again:");
				           while (getchar() != '\n')
				                ;
				            ch = getchar();
				            ch = toupper (ch);
			    }
			}
		}
	if (ch == 'Y')
		strcpy(changedNode->ingredientName, buffer);
	printIngredientItemNode(changedNode);
}

/********************************************************************************************************************
* 																													*
*	 			modifies the cupsPerGram amount in an existing ingredientType node in the linked-list 				*
*																													*
*********************************************************************************************************************/
void modifyIngredientItemNodeWeight(struct ingredientItem *node){
	struct ingredientItem *changedNode = node;
	char ch = '\0';
	float gramsPerCup = 0.00;
	printIngredientItemNode(changedNode);
	while (ch != 'Y'){	
		while (gramsPerCup == 0.00){
			printf("\n\t\tEnter New Ingredient Weight In Grams: ");
	    	if (scanf(" %f", &gramsPerCup) != 1){
	       	 	printf("\t\tInvalid Entry");
	        	while (getchar() != '\n')
	            	;
	           }
	       }
	       while (getchar() != '\n')
	        ;
	    printf("\n\t\tYou Entered: '%f grams', Is This Correct (y/n)?: ", gramsPerCup);
	    ch = getchar();
	    ch = toupper(ch);
	    switch (ch) {
	       	case 'Y' : break;
	       	case 'N' : gramsPerCup = 0.00;
	       			   break;
	       	default  : printf("\n\t\tInvalid Selection, Try Again:");
	    }
    }
    changedNode->gramsPerCup = gramsPerCup;
    printIngredientItemNode(changedNode);
}

/********************************************************************************************************************
* 																													*
*	 			modifies the tablespoonFlag in an existing ingredientType node in the linked-list 					*
*																													*
*********************************************************************************************************************/
void modifyIngredientItemNodeFlag(struct ingredientItem *node){
	struct ingredientItem *changedNode = node;
	char choice = '\0';
	char measurementType = '\0';
	while (choice != 'Y'){
		printf("\n\t\tEnter Measurement Type (cups/tbsp): ");
		measurementType = '\0';
		while ((measurementType != 'C') && (measurementType != 'T')){
			measurementType = getchar();
			measurementType = toupper(measurementType);
			switch (measurementType){
			    case 'C': 	break;
				case 'T': 	break;
				default:	printf("\t\tInvalid Selection, Try Again: ");
			   	  		   	while (getchar() != '\n')
			    	      	  ;
			}
		}
		while ((getchar()) != '\n')
		    ;
		printf("\n\t\tYou Entered: \"");
		printf((measurementType == 'T') ? "g/tbsp" : "g/cups");
		printf("\", Is This Correct (y/n)?: ");
		while ((choice != 'Y') && (choice != 'N')){
		    choice = getchar();
		    choice = toupper(choice);
		    switch (choice) {
			    case 'Y' : break;
			    case 'N' : break;
			    default  : printf("\t\tInvalid Selection, Try Again: ");
			}
		while (getchar() != '\n')
			;
		}
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
	printf("\t\t~%s~\n\n\t\t%.2f", node->ingredientName, node->gramsPerCup);
	printf(node->tablespoonFlag == 1 ? " g/tbsp" : "g/cups");
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
	printf("\n\t\t");
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
*	 			delete a an ingredientItem node						 				 								*
*				returns 0 on success, 1 on cancel, -1 on failure																	*
*																													*
*********************************************************************************************************************/
int deleteIngredientItemNode(struct ingredientType *head, char buffer[INGREDIENT_BUFFER_LEN]){
	//reuse code form findIngredientItemNode to find node:
	//create array of pointers to store possible found ingredients, make sure it is NULL to start
	struct ingredientItem *foundIngredients[MAX_INGREDIENTS_FOUND] = {NULL};
	memset(foundIngredients, 0, sizeof(foundIngredients));
	//need to make an array for ingredientTypes that match the found ingredientItems so I can pass in that for dump
	struct ingredientType *foundIngredientsTypes[MAX_INGREDIENTS_FOUND] = {NULL};
	memset(foundIngredientsTypes, 0, sizeof(foundIngredientsTypes));
	
	unsigned int ingredientItemCounter = 0;
	unsigned int ingredientItemChoice = 0;
	//iterate through all sub-lists from the head node of the ingredientType linked list searching for partial matches
	//store partial matches in array to share with user
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
	if (ingredientItemCounter == 0){
		printf("%s Not Found\n", buffer);
		return -1;
	}
	if (ingredientItemCounter == 1)
		;
	//if there are multiple possible choices in the array, print them, then ask for the user to pick (with safety)
	else if (ingredientItemCounter > 1){
		for (int i = 1; i <= ingredientItemCounter; i++)
			printf("\t\t%i) %s\n", i, foundIngredients[i-1]->ingredientName);
		while ((ingredientItemChoice == 0) || ((ingredientItemChoice <= 0) || (ingredientItemChoice > ingredientItemCounter))){
        	printf("\t\tEnter Ingredient Number: ");
	   		if ((scanf(" %i", &ingredientItemChoice) != 1) || 
	       	   ((ingredientItemChoice <= 0) || (ingredientItemChoice > ingredientItemCounter))){
	       			printf("\t\tInvalid Entry\n");
	       			while (getchar() != '\n')
	           			;
	        }
	    }
	}
	char confirm = '\0';
	printf("\n\t\t%s Found, ", foundIngredients[ingredientItemChoice-1]->ingredientName);
	while ((confirm != 'Y') && (confirm !='N')){
		printf("Confirm DELETE (y/n): ");
		confirm = getchar();
		confirm = toupper(confirm);
		switch (confirm) {
			case 'Y': break; //change back to break to check next functionality
			case 'N': return 1;
			default : printf("\n\t\tInvalid Entry, Try Again\n\t\t"); 	
					  while (getchar() != '\n')
					  	;
		}
	}
	//delete functionality
	struct ingredientItem *cur = NULL;
	struct ingredientItem *prev = NULL;
	struct ingredientItem *next = NULL;
	
	cur = foundIngredients[ingredientItemChoice-1];
	next = cur->next;
	prev = cur->prev;
	//if prev == NULL, it is the first node;
	if (!prev)
		foundIngredientsTypes[ingredientItemChoice-1]->head = next;
	//if it is a middle node
	else if (prev !=NULL && next != NULL){
		prev->next = next;
		next->prev = prev;
	}
	//if it is the final node
	else if (prev && (next == NULL)){
		prev->next = NULL;
	}
	free(cur);
	cur = NULL;
	//reset to head and reattach head to the ingredientType's head member;
	while (prev->prev != NULL)
		prev = prev->prev;
	foundIngredientsTypes[ingredientItemChoice-1]->head = prev;
	//dump changed ingredientItem linked list to .txt file
	dumpIngredientItemList(foundIngredientsTypes[ingredientItemChoice-1]);
	return 0;
}