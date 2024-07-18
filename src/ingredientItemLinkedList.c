#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
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
//REDO TO MEET AGNOSTIC OS DECISIONS fread() fwrite() change to fscanf() fprintf() and move through '\0' nodes

struct ingredientItem *loadIngredientItem(struct ingredientType *node){
	FILE *fp = NULL;
	struct ingredientType *ingredientType = node;
	struct ingredientItem *cur = NULL;

	char openFileBuffer[INGREDIENT_BUFFER_LEN+15] ={'\0'};
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
    for (int i = 1; i < numNodes; i++){
    	struct ingredientItem *newNode = NULL;
    	if ((newNode = createIngredientItemNode()) == NULL){
    	    fprintf(stderr, "Unable to Create Ingredient Item Node to Load List\n");
    		fp = NULL;
    		return NULL;
    	}
    	//need to redo this to match the add structure and how that will print out
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
	struct ingredientItem *cur = ingredientTypeNode->ingredientItem;
	while (cur){
		fprintf(fp, "%s\t\t%f\n", cur->ingredientName, cur->gramsPerCup);
		cur = cur->next;
	}
	fclose(fp);
	fp = NULL;
	return 0;
}

/********************************************************************************************************************
* 																													*
*	 			add a new node into the ingredientItem linked-list alphabetically									*
*				returns pointer to head on success, NULL on failure													*
*																													*
*********************************************************************************************************************/

