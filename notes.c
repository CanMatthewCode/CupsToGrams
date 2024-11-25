/********************************************************************************************************************
* 																													*
*	  			text 								*
*																													*
*********************************************************************************************************************/

("*\t\t\t\t\t\t\t\t*")

"*****************************************************************" 65 CHARACTERS

void decimalPlaceCheck(float ingredientGrams, char *bufferToFill){
	float check = ingredientGrams - (int)ingredientGrams;
	if (check == 0)
		sprintf(bufferToFill, "%7d", (int)ingredientGrams);
	else{
		sprintf(bufferToFill, "%7.2f", ingredientGrams);
		int bufferSize = strlen(bufferToFill);
		while (*(bufferToFill + bufferSize - 1) == '0'){
				(*(bufferToFill + bufferSize - 1) = '\0');
				bufferSize--;
		}
	}
}