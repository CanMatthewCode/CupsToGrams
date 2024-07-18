#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "ingredientConversions.h"
#include "ingredientTypeLinkedList.h"
#include "ingredientItemLinkedList.h"

/*		Load from text file sub-ingredientItemLinkedList for each opened ingredientTypeNode->typeName.txt
*		Check if wanted ingredientType exists already in node
*		Create new node for ingredientTypeLinkedList
*		Populate and Add new node to ingredientItemLinkedList
*		Delete selected node
*		Print ingredient node list
*		Dump ingredientTypeLinkedList into text file named ingredientType->ingredientName
*		Free ingredientTypeLinkedList 
*/

/************************************************************************************************************
* 																											*
*	  	loadIngredientItem loads the ingredientsItems linked-list associated with an ingredientType pointer *
*		loads a .txt file from the typeName buffer in the ingredientType struct								*
*		returns a pointer to ingredientItem link-list head on success, NULL on failure						*
*																											*
*************************************************************************************************************/
//REDO TO MEET AGNOSTIC OS DECISIONS fread() fwrite() change to fscanf() fprintf() and move through '\0' nodes
/*
struct ingredientItem *loadIngredientItem(struct ingredientType *node){
	FILE *fp = NULL;
	struct ingredientType *ingredientType = node;
	struct ingredientItem *cur = NULL;

	char openFileBuffer[INGREDIENT_BUFFER_LEN+4] ={'\0'};
	//copy name from struct node into ingredientTypeBuffer and then into openFileBuffer to store and use
	strcpy(openFileBuffer, ingredientType->typeName);
	//append .txt to ingredientType names
	strcat(openFileBuffer, ".txt");
	if ((fp = fopen(openFileBuffer, "r+")) == NULL){
		if ((fp = fopen(openFileBuffer, "w+")) == NULL)
			return NULL;
	}
	//functionality to populate a linked list from the "IngredientTypes.txt" file and return pointer to head
	long structsize = sizeof(struct ingredientItem) - sizeof(struct ingredient item *);
	fseek(fp, 0l, SEEK_END);
	long filePosition = ftell(fp);
	int numNodes = (filePosition / structSize);
	
	//loop to populate the link list backwards from the text file
    for (int i = 1; i < numNodes; i++){
    	fseek(fp, -(structSize * i), SEEK_END);
    	struct ingredientItem *newNode = NULL;
    	if ((newNode = createIngredientItemNode()) == NULL){
    		fp = NULL;
    		return NULL;
    	}
    	if (fread(newNode, structSize, 1, fp) != 1){
    		fprintf(stderr, "Unable to populate Ingredient Items from %s\n", openFileBuffer);
    		free(newNode);
    		fclose(fp);
    		fp = NULL;
    		return NULL;
    	}
    	newNode->next = cur;
    	cur = newNode;
    }
    ingredientType->ingredientItem = cur;
    fclose(fp);
    fp = NULL;
    return ingredientType->ingredientItem;
}
*/