#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "ingredientconversions.h"
#include "ingredientTypeLinkedList.h"

/************************************************************************************************************
* 																											*
*	  	loadIngredientTypes loads the ingredientsTypes linked-list from an IngredientTypes.txt file			*
*		returns a pointer to ingredientType link-list head on success, NULL on failure						*
*																											*
*************************************************************************************************************/
struct ingredientType *loadIngredientTypes(struct ingredientType *head){
	FILE *fp = NULL;
	struct ingredientType *cur = head;
	//open linked list of ingredient types which each have their own linked list inside
	if((fp = fopen("IngredientTypes.txt", "r+")) == NULL){
		if((fp = fopen("IngredientTypes.txt", "w+")) == NULL)
			return NULL;	
	}
	//add functionality to populate a linked list from the "IngredientTypes.txt" file and return pointer to head
	long structSize = (sizeof(struct ingredientType) - sizeof(struct ingredientType *) - sizeof(struct ingredientItem *));
	fseek(fp, 0l, SEEK_END);
    long filePosition = ftell(fp);
    int numNodes = (filePosition / structSize);
    
    //loop to populate the link list backwards from the text file
    for (int i = 1; i < numNodes; i++){
    	fseek(fp, -(structSize * i), SEEK_END);
    	struct ingredientType *newNode = NULL;
    	if ((newNode = createNode()) == NULL)
    		return NULL;
    	if (fread(newNode, structSize, 1, fp) != 1){
    		fprintf(stderr, "Unable to populate Ingredient Types\n");
    		free(newNode);
    		fclose(fp);
    		return NULL;
    	}
    	newNode->next = cur;
    	cur = newNode;
    }
    fclose(fp);
    return head;
}

/************************************************************************************************************
* 																											*
*	  	create a new node memory block with malloc for an ingredientType linked-list node	 				*
*		returns a pointer to the new memory block on success, NULL on failure								*
*																											*
*************************************************************************************************************/
struct ingredientType *createNode(void){
	struct ingredientType *ingredientTypePointer = malloc(sizeof(struct ingredientType));
	if (ingredientTypePointer == NULL){
		perror("Failure to allocate memory for ingredientType node");
		return NULL;
	}
	//set pointers in node to NULL for safety
	ingredientTypePointer->head = NULL;
	ingredientTypePointer->next = NULL;
	return ingredientTypePointer;
}

/************************************************************************************************************
* 																											*
*	 	check user input key against existing ingredientTypes list											*
*		returns pointer to node found on success, NULL on failure											*
*																											*
*************************************************************************************************************/
struct ingredientType *findIngredientType(struct ingredientType *head, char buffer[INGREDIENT_BUFFER_LEN]){
	struct ingredientType *cur = head;
	printf("Enter Ingredient Type: ");
	readUserInputIntoBuffer(buffer);
	while (cur){
		if (strcmp(buffer, cur->typeName) > 0)
			cur = cur->next;
		if (strcmp(buffer, cur->typeName) == 0)
			return cur;
		if (strcmp(buffer, cur->typeName) < 0){
			return NULL;
		}
	}
	if (cur == NULL)
		return NULL;
}

/************************************************************************************************************
* 																											*
*	 	add a new node into the ingredientType linked-list alphabetically									*
*		returns pointer to newly inserted node on success, NULL on failure									*
*																											*
*************************************************************************************************************/
struct ingredientType *addNewIngredientTypeNode(struct ingredientType *head){
	//take the key, compare it in a loop to the current node's typeName and the next->typeName.  
	//If it is bigger than the current, but smaller than than the next->,
	//create a new node and add the key into the typeName then insert it into location between the two nodes
	//return pointer to new node
	struct ingredientType *find;
	char buffer[INGREDIENT_BUFFER_LEN];
	if ((find = findIngredientType(head, buffer)) != NULL){
		printf("Ingredient Type Already Exists");
		return NULL;
	}
	struct ingredientType *cur = NULL;
	struct ingredientType *prev = NULL;
	struct ingredientType *newNode = NULL;
	newNode = createNode();
	for (cur = ingredientTypePointer; cur != NULL && (strcmp(buffer, cur->typeName) > 0); prev = cur, cur=cur->next)
		;
	//if cur == NULL it is the first node
	if (cur == NULL){
		strcpy(newNode->typeName, buffer);
		return newNode;
	}
	if ((strcmp(buffer, cur->typeName) > 0) && ((strcmp(buffer, cur->next->typeName) < 0) || cur->next == NULL)){
		strcpy(newNode->typeName, buffer);
		prev->next = newNode;
		newNode->next = cur;
	} 
	return newNode;
}

/************************************************************************************************************
* 																											*
*	 	print all ingredient types currently stored in the ingredientType linked-list head					*
*																											*
*************************************************************************************************************/
void printIngredientTypeList(struct ingredienType *head){
	struct ingredientType *cur = NULL;
	int counter = 1;
	puts("INGREDIENT TYPES AVAILABLE:");
	for (cur = head; cur; counter++, cur = cur->next){
		printf("%s\t", cur->typeName);
		if (counter % 5 == 0)
			printf("\n");
	}
}

/************************************************************************************************************
* 																											*
*	 	dump the ingredient type names from linked-list into link IngredientTypes.txt file					*
*		returns -1 on failure to open IngredientTypes.txt file, return 0 on successful dump					*
*																											*
*************************************************************************************************************/
int dumpIngredientTypeList(struct ingredientType *head){
	FILE *fp = NULL;
	struct ingredientType *cur = head;
	long structSize = (sizeof(struct ingredientType) - sizeof(struct ingredientType *) - sizeof(struct ingredientItem *));
	if ((fp = fopen ("IngredientTypes.txt", "w+")) == NULL){
		printf("Unable to open ingredientTypes.txt file\n");
		fclose(fp);
		return -1;
	}
	while (cur){
		fwrite(cur, structSize, 1, fp);
		cur = cur->next;
	}
	fclose(fp);
	return 0;
}

/************************************************************************************************************
* 																											*
*	 	free full ingredientType linked-list from memory													*
*																											*
*************************************************************************************************************/
void freeIngredientTypeList(struct ingredientType *head){
	struct ingredientType *cur = head;
	struct ingredientType *temp;
	while (cur){
		temp = cur;
		cur = cur->next;
		free(temp);
	}
}

/************************************************************************************************************
* 																											*
*	 	delete node permanently from ingredientType linked-list												*
*		returns ingredientType pointer to head on success, NULL on failure or cancel						*
*																											*
*************************************************************************************************************/
struct ingredientType *deleteIngredientTypeNode(struct ingredientType *head){
	char buffer[INGREDIENT_BUFFER_LEN];
	readUserInputIntoBuffer(buffer);
	struct ingredientType *cur = head;
	struct ingredientType *prev = NULL;
	struct ingredientType *next = cur->next;
	char confirm = '\0';
	while (cur && (strcmp(buffer, cur->typeName) != 0)){
		prev = cur;
		cur = cur->next;
		cur->next = cur->next;
	}
	if (cur == NULL){
		printf("Ingredient Type Not Found In List\n");
		return NULL;
	}
	if (strcmp(buffer, cur->typeName) == 0){
		printf("%s Found, ", buffer);
		while ((confirm != 'y') && (confirm !='n')){
			printf("Confirm Delete (y/n): ");
			confirm = getchar();
			confirm = tolower(confirm);
			switch (confirm) {
				case 'y': break;
				case 'n': return NULL;
				default : printf("Invalid Entry, Try Again\n"); 	
			}
			while (getchar() != '\n')
			    ;
		}
	}
	prev->next = cur->next;
	free(cur);
}