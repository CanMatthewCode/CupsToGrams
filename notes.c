/********************************************************************************************************************
* 																													*
*	  			text 								*
*																													*
*********************************************************************************************************************/

("*\t\t\t\t\t\t\t\t*")

"*****************************************************************" 65 CHARACTERS


/************************************************************************************************************
* 																											*
*				menu for finding recipe from the recipeStruct headPointer									*
*				and then printing chosen recipe out as a PDF document										*
*																											*
*************************************************************************************************************/
void printRecipeToPDFMenu(struct recipeStruct *recipeHeadPointer){
	struct recipeStruct *foundRecipe = NULL;
	char buffer[INGREDIENT_BUFFER_LEN] = {'\0'};
	clearScreen();
	puts("\n\n\t\t*********************************************************************************");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*\t\t\t      -PRINT RECIPE TO PDF- \t\t\t\t*");
	puts("\t\t*\t\t\t\t\t\t\t\t\t\t*");
	puts("\t\t*********************************************************************************");
	printf("\n\t\tEnter Recipe Name To Save As A PDF Document: ");
	readUserInputIntoBuffer(buffer);
	foundRecipe = findRecipe(recipeHeadPointer, buffer);
	if (foundRecipe)
			printFullRecipe(foundRecipe);
	char choice = '\0';
	printf("\n\t\tPrint To PDF (y/n)? ");
	YESNOCHOICE(choice);
	if (choice == 'N')
		return;
	else 
		printRecipeToPDF(foundRecipe);
}
