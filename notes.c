/********************************************************************************************************************
* 																													*
*	  			text 								*
*																													*
*********************************************************************************************************************/

("*\t\t\t\t\t\t\t\t*")

"*****************************************************************" 65 CHARACTERS



//	put new member in ingredientStruct:
	int nonWeightedIngredientFlag;
		
//	put in addNewNonMeasuredIngredient function:
	currentRecipe->nonWeightedIngredientFlag = 1;
		
//	put in printRecipeIngredients:
	if (recipe->nonWeightedIngredientFlag == 1){
		printf("\t\t%d)  %7.2f of %s ", i, recipe->ingredients[i].ingredientGrams, recipe->ingredients[i].ingredientName);
		if (strlen(recipe->ingredients[i].userCupsInput) > 0)
			printf("(%s)\n", ingredients[i].userCupsInput);
		else (printf("\n"));
	} else {
		printf("\t\t%d)  %s\n", i + 1, recipe->recipeInstructions[i]);
	}
		
//	put in dumpRecipesFromLinkedList:
	while (counter < recipe->numberOfIngredients){
		fprintf(fp, "\n%d\t%s\t%s\t%.2f", recipe->ingredients[counter].nonWeightedIngredientFlag, recipe->ingredients[counter].ingredientName, recipe->ingredients[counter].userCupsInput, recipe->ingredients[counter].ingredientGrams);
		counter++;
	}
		
//	put in loadRecipesToLinkedList:
	for (int i = 0; i < newNode->numberOfIngredients; ++i){
		fscanf(fp, " %d", &recipe->ingredients[i].nonWeightedIngredientFlag;
		while ((ch = fgetc(fp)) != '\t');
    	int counter = 0;
    	while ((ch = fgetc(fp)) != '\t')
    		newNode->ingredients[i].ingredientName[counter++] = ch;
    	counter = 0;
    	while ((ch = fgetc(fp)) != '\t')
    		newNode->ingredients[i].userCupsInput[counter++] = ch;
    	fscanf(fp, " %f ", &newNode->ingredients[i].ingredientGrams);
    }

//	put in printRecipeToPDF:
	int lineCounter = 0;
	for (int i = 0; i < recipeToPrint->numberOfIngredients; i++){
		memset(ingredientBuffer, 0, sizeof(ingredientBuffer));
		if (recipeToPrint->ingredients[i].nonWeightedIngredientFlag == 1){
			if (strlen(recipeToPrint->ingredients[i].userCupsInput) > 0) //print the recipe w/ the () bracket info  if not print the recipe to buffer w/out, then only print to pdf once
				sprintf(ingredientBuffer, "%d) %7.2f grams of %s (%s)", i + 1, recipeToPrint->ingredients[i].ingredientGrams, recipeToPrint->ingredients[i].ingredientName, recipeToPrint->ingredients[i].userCupsInput);
			else (sprintf(ingredientBuffer, "%d) %7.2f grams of %s", i + 1, recipeToPrint->ingredients[i].ingredientGrams, recipeToPrint->ingredients[i].ingredientName);
			pdf_add_text(pdf, NULL, ingredientBuffer, 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
			linePointCounter += V_FONT_POINTS;
			lineCounter++;
		} else {
			sprintf(ingredientBuffer, "%d) %7.2f grams of %s (%s)", i + 1, recipeToPrint->ingredients[i].ingredientGrams, recipeToPrint->ingredients[i].ingredientName, recipeToPrint->ingredients[i].userCupsInput);
			pdf_add_text(pdf, NULL, ingredientBuffer, 12, SIDE_MARGIN, TOTAL_VERTICAL_POINTS - TOP_BOTTOM_MARGIN - linePointCounter, PDF_BLACK);
			linePointCounter += V_FONT_POINTS;
			lineCounter++;
		}
	}