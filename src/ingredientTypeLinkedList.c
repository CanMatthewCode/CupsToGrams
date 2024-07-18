#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"

/********************************************************************************************************************
* 																													*
*	  			loadIngredientTypes loads the ingredientsTypes linked-list from an IngredientTypes.txt file			*
*				returns a pointer to ingredientType link-list head on success, NULL on failure						*
*																													*
*********************************************************************************************************************/
struct ingredientType *loadIngredientTypes(void){
	FILE *fp = NULL;
	struct ingredientType *cur = NULL;
	//open linked list of ingredient types which each have their own linked list inside
	if((fp = fopen("IngredientTypes.txt", "r+")) == NULL){
		if((fp = fopen("IngredientTypes.txt", "w+")) == NULL){
			fp = NULL;
			return NULL;
		}
	}
	//functionality to populate a linked list from the "IngredientTypes.txt" file and return pointer to head
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
    	struct ingredientType *newNode = NULL;
    	if ((newNode = createIngredientTypeNode()) == NULL){
    		fprintf(stderr, "Unable to Create Ingredient Types Node to Load List\n");
    		fp = NULL;
    		return NULL;
    	}
    	if (fgets(newNode->typeName, sizeof(newNode->typeName), fp) == NULL){
    		fprintf(stderr, "Unable to populate Ingredient Types Node\n");
    		free(newNode);
    		fp = NULL;
    		return NULL;
    	}
    	if (newNode->typeName[strlen(newNode->typeName)-1] == '\n')
    			newNode->typeName[strlen(newNode->typeName)-1] = '\0';
    	//if prev is NULL this is the first node in the linked list and is therefore head, otherwise, link backwards
    	if (cur == NULL)
    		cur = newNode;
    	else {
    		cur->next = newNode;
    		newNode->prev = cur;
    		cur = newNode;
    	}
    }
    rewind(fp);
    fclose(fp);
    fp = NULL;
    while (cur->prev != NULL)
    	cur = cur->prev;
    return cur;
}

/********************************************************************************************************************
* 																													*
*	  			create a new node memory block with malloc for an ingredientType linked-list node		 			*
*				returns a pointer to the new memory block on success, NULL on failure								*
*																													*
*********************************************************************************************************************/
struct ingredientType *createIngredientTypeNode(void){
	struct ingredientType *ingredientTypeNode = calloc(1, sizeof(struct ingredientType));
	if (ingredientTypeNode == NULL){
		perror("Failure to allocate memory for ingredientType node");
		ingredientTypeNode = NULL;
		return NULL;
	}
	return ingredientTypeNode;
}

/********************************************************************************************************************
* 																													*
*	 			check user input key against existing ingredientTypes list											*
*				returns pointer to node found on success, NULL on failure											*
*																													*
*********************************************************************************************************************/
struct ingredientType *findIngredientType(struct ingredientType *head, char buffer[INGREDIENT_BUFFER_LEN]){
	struct ingredientType *cur = NULL;
	for (cur = head; cur != NULL; cur=cur->next)
		if (strcmp(buffer, cur->typeName) == 0)
			return cur;
	return NULL;
}


/********************************************************************************************************************
* 																													*
*	 			add a new node into the ingredientType linked-list alphabetically									*
*				returns pointer to head on success, NULL on failure													*
*																													*
*********************************************************************************************************************/
struct ingredientType *addNewIngredientTypeNode(struct ingredientType *head, char buffer[INGREDIENT_BUFFER_LEN]){
	struct ingredientType *cur = head;
	struct ingredientType *prev = NULL;
	struct ingredientType *newNode = NULL;
	
	newNode = createIngredientTypeNode();
	
	strcpy(newNode->typeName, buffer);
	//if cur == NULL it is the first node
	if (cur == NULL){
		return newNode;
	}
	//if buffer is smaller than 1st node, it is new 1st node
	if ((cur != NULL) && (strcmp(newNode->typeName, cur->typeName) < 0)){
		newNode->next = cur;
		cur->prev = newNode;
		return newNode;
	}
	
	for ( ; cur->next != NULL && (strcmp(newNode->typeName, cur->typeName) > 0); prev = cur, cur=cur->next)
		;	
	if (strcmp(newNode->typeName, cur->typeName) == 0){
		printf("Ingredient Type Already Exists\n");
	}
	//all middle cases
	if ((strcmp(newNode->typeName, prev->typeName) > 0) && 
	   (strcmp(newNode->typeName, cur->typeName) < 0)){
		newNode->prev = prev;
		newNode->next = cur;
		prev->next = newNode;
		cur->prev = newNode;
	} 
	//final node case
	if ((strcmp(newNode->typeName, cur->typeName) > 0) && cur->next == NULL){
		newNode->prev = cur;
		cur->next = newNode;

	}
	while (cur->prev != NULL)
		cur=cur->prev;
	return cur;
}

/********************************************************************************************************************
* 																													*
*	 			print all ingredient types currently stored in the ingredientType linked-list head					*
*																													*
*********************************************************************************************************************/
void printIngredientTypeList(struct ingredientType *head){
	struct ingredientType *cur = NULL;
	int counter = 0;
	puts("\t\t*****************************************************************");
	puts("\t\t*\t\t\t\t\t\t\t\t*");
	puts("\t\t*\t\t  -INGREDIENT TYPES AVAILABLE:-      \t\t*");
	puts("\t\t*\t\t\t\t\t\t\t\t*");
	puts("\t\t*****************************************************************\n\n");
	printf("\t\t");
	for (cur = head; cur; cur = cur->next){
		printf("%-19s", cur->typeName);
		counter++;
		if (counter % 4 == 0)
			printf("\n\n\t\t");
	}
	while (getchar() != '\n')
		;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t(Press Enter to Continue)");
}

/********************************************************************************************************************
* 																													*
*	 			dump the ingredient type names from linked-list into link IngredientTypes.txt file					*
*				returns -1 on failure to open IngredientTypes.txt file, return 0 on successful dump					*
*																													*
*********************************************************************************************************************/
int dumpIngredientTypeList(struct ingredientType *head){
	FILE *fp = NULL;
	struct ingredientType *cur = head;
	if ((fp = fopen ("IngredientTypes.txt", "w+")) == NULL){
		printf("Unable to open ingredientTypes.txt file\n");
		return -1;
	}
	while (cur){
		fprintf(fp, "%s\n", cur->typeName);
		cur = cur->next;
	}
	fclose(fp);
	fp = NULL;
	return 0;
}

/********************************************************************************************************************
* 																													*
*	 			free full ingredientType linked-list from memory													*
*																													*
*********************************************************************************************************************/
void freeIngredientTypeList(struct ingredientType *head){
	struct ingredientType *cur = head;
	struct ingredientType *temp;
	while (cur){
		temp = cur;
		cur = cur->next;
		free(temp);
	}
	temp = NULL;
}

/**********************************************************************************************************v*********
* 																													*
*	 			delete node permanently from ingredientType linked-list												*
*				returns ingredientType pointer to head on success, NULL on failure or cancel						*
*																													*
*********************************************************************************************************************/
struct ingredientType *deleteIngredientTypeNode(struct ingredientType *head){
	struct ingredientType *cur = head;
	struct ingredientType *prev = NULL;
	struct ingredientType *next = NULL;
	struct ingredientType *headPointer = head;
	puts("\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	puts("\t\tx\t\t\t\t\t\t\t\tx");
	puts("\t\tx\t\t      -DELETE INGREDIENT TYPE- \t\t\tx");
	puts("\t\tx\t\t\t\t\t\t\t\tx");
	puts("\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	printf("\n\n\t\tEnter Ingredient Type to PERMANENTLY DELETE: ");
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	readUserInputIntoBuffer(buffer);
	char confirm = '\0';
	if (cur == NULL){
		printf("\t\tIngredient Type List is Empty\n");
		return NULL;
	}
	cur = findIngredientType(cur, buffer);
	if (cur == NULL){
		printf("\t\tIngredient Type Not Found In List (Hit Enter to Continue)");
		return headPointer;
	}
	printf("\n\t\t%s Found, ", buffer);
	while ((confirm != 'y') && (confirm !='n')){
		printf("Confirm Delete (y/n): ");
		confirm = getchar();
		confirm = tolower(confirm);
		switch (confirm) {
			case 'y': break; //change back to break to check next functionality
			case 'n': return headPointer;
			default : printf("\n\t\t***Invalid Entry, Try Again***\n\t\t"); 	
					  while (getchar() != '\n')
					  	;
		}
	}
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
	else if(prev && next==NULL)
		prev->next=NULL;
	free(cur);
	cur = NULL;
	//dump to .txt file
	dumpIngredientTypeList(headPointer);
	return headPointer;
}