/********************************************************************************************************************
* 																													*
*	  			text 								*
*																													*
*********************************************************************************************************************/

("*\t\t\t\t\t\t\t\t*")

"*****************************************************************" 65 CHARACTERS

float typeOfMeasurement(char *typeToConvert, int *weightedInputFlag){
	if ((strcmp(typeToConvert, "Cups") == 0) || (strcmp(typeToConvert, "Cup") == 0) || (strcmp(typeToConvert, "C") == 0)){
		return 1;
	} else if ((strcmp(typeToConvert, "Tablespoons") == 0) || (strcmp(typeToConvert, "Tablespoon") == 0) || (strcmp(typeToConvert, "Tbsp") == 0) || (strcmp(typeToConvert, "Tbl") == 0) || (strcmp(typeToConvert, "Tbls") == 0)) {
		return 16;
    } else if ((strcmp(typeToConvert, "Teaspoons") == 0) || (strcmp(typeToConvert, "Teaspoon") == 0) || (strcmp(typeToConvert, "Tsp") == 0) || (strcmp(typeToConvert, "Tea") == 0)){
		return 48;
	} else if ((strcmp(typeToConvert, "Ounces") == 0) || (strcmp(typeToConvert, "Ounce") == 0) || (strcmp(typeToConvert, "Ozs") == 0) || (strcmp(typeToConvert, "Oz") == 0)) {
		*weightedInputFlag = 1;
		return (1 / 28.34952); //28.34962 is the number of grams per oz - return 1 divided by it so the input is multiplied in the returning function
	} else if ((strcmp(typeToConvert, "Pounds") == 0) || (strcmp(typeToConvert, "Pound") == 0) || (strcmp(typeToConvert, "Lbs") == 0) || (strcmp(typeToConvert, "Lb") == 0)) {
		*weightedInputFlag = 1;
		return (1 / 453.59237); //453.59237 is the number of grams per pound - return 1 divided by it so the input is multiplied in the returning function 
	} else if ((strcmp(typeToConvert, "Grams") == 0) || (strcmp(typeToConvert, "Gram") == 0) || (strcmp(typeToConvert, "G") == 0) || (strcmp(typeToConvert, "Gs") == 0)) {
		*weightedInputFlag = 1;
		return 1;
	} else 
	    return 0;
}


float cupsToGrams(char *cupsInputAmountBuffer, struct ingredientItem *ingredientToConvert){
	char measurementAmount[20] = {'\0'};
	char measurementType[12] = {'\0'};
	int charsRead = 0;
	int weightedInputFlag = 0;
	float sum = 0;
	char *currentPosition = NULL;
	printf("\n\n\n\t\t\"Cups, Tablespoons, Teaspoons, Pounds, Oz\"");
	printf("\n\n\t\tEnter Amount Of \'%s\' To Convert: ", ingredientToConvert->ingredientName);
	do {
		memset(cupsInputAmountBuffer, 0, 20);
		memset(measurementAmount, 0, sizeof(measurementAmount));
		memset(measurementType, 0, sizeof(measurementType));
		charsRead = 0;
		readUserInputIntoBuffer(cupsInputAmountBuffer);
		currentPosition = cupsInputAmountBuffer;
		//move through cupsInputAmountBuffer reading the numbers then types in a loop
		do {
			if (sscanf(currentPosition, " %19[0-9/. ]%19[A-Za-z]%n", measurementAmount, measurementType, &charsRead) == 2) {
			//safety for if typeOfMeasurement returns 0 for wrong input
				if (typeOfMeasurement(measurementType, &weightedInputFlag) == 0){
					break;
				}
				sum += ((getCups(measurementAmount)) / (typeOfMeasurement(measurementType, &weightedInputFlag)));
				currentPosition += charsRead; 
			} else {
				break; //exit the loop if sscanf() fails to read two input items
			}
		} while (*currentPosition != '\0');
		if (ingredientToConvert->tablespoonFlag == 1)
			sum *= 16;
		if (sum == 0){
			printf("\n\t\t%s: Not Valid Input, Try Again: ", cupsInputAmountBuffer);
		}
	} while (sum == 0);
	//add function here to create standard output notation & store it then pass it into typeOfMeasurement and store it and measurementAmount in to the passed in cupsInputAmountBuffer after wiping it clean
	//unifyMeasurementTypes(cupsInputAmountBuffer, measurementAmount, measurementType, sum);
	if (weightedInputFlag == 0)
		return sum*ingredientToConvert->gramsPerCup;
	else
		return sum;
}


//takes in the cupsInputAmountBuffer, the measurementAmount buffer, and the MeasurementType buffer
//uses measurement type to determine plural
//scan the type and create a unified type set of measurements - if grams were passed in, the userinputbuffer is wiped after

/********************************************************************************************************************
* 																													*
*	  			takes the parsed user input for amount and amount type and unifies it into a 						*
*				standard notation. Uses sum to check for plurality													*
*																													*
*********************************************************************************************************************/
void unifyMeasurementTypes(char *cupsInputAmountBuffer, char *measurementAmount, char *typeToConvert, float sum){
	if ((strcmp(typeToConvert, "Cups") == 0) || (strcmp(typeToConvert, "Cup") == 0) || (strcmp(typeToConvert, "C") == 0)){
		memset(cupsInputAmountBuffer, 0, sizeof(cupsInputAmountBuffer));
		if (sum > 1)
			strcpy(cupsInputAmountBuffer, "%s Cups", measurementAmount);
		else
			strcpy(cupsInputAmountBuffer, "%s Cup", measurementAmount);
		return;
	} else if ((strcmp(typeToConvert, "Tablespoons") == 0) || (strcmp(typeToConvert, "Tablespoon") == 0) || (strcmp(typeToConvert, "Tbsp") == 0) || (strcmp(typeToConvert, "Tbl") == 0) || (strcmp(typeToConvert, "Tbls") == 0)) {
		memset(cupsInputAmountBuffer, 0, sizeof(cupsInputAmountBuffer));
		if (sum > 1)
			strcpy(cupsInputAmountBuffer, "%s Tbsps", measurementAmount);
		else
			strcpy(cupsInputAmountBuffer, "%s Tbsp", measurementAmount);
		return;
    } else if ((strcmp(typeToConvert, "Teaspoons") == 0) || (strcmp(typeToConvert, "Teaspoon") == 0) || (strcmp(typeToConvert, "Tsp") == 0) || (strcmp(typeToConvert, "Tea") == 0)){
		memset(cupsInputAmountBuffer, 0, sizeof(cupsInputAmountBuffer));
		if (sum > 1)
			strcpy(cupsInputAmountBuffer, "%s Tsps", measurementAmount);
		else
			strcpy(cupsInputAmountBuffer, "%s Tsp", measurementAmount);
		return;
	} else if ((strcmp(typeToConvert, "Ounces") == 0) || (strcmp(typeToConvert, "Ounce") == 0) || (strcmp(typeToConvert, "Ozs") == 0) || (strcmp(typeToConvert, "Oz") == 0)) {
		memset(cupsInputAmountBuffer, 0, sizeof(cupsInputAmountBuffer));
		if (sum > 1)
			strcpy(cupsInputAmountBuffer, "%s Ozs", measurementAmount);
		else
			strcpy(cupsInputAmountBuffer, "%s Oz", measurementAmount);
		return;
	} else if ((strcmp(typeToConvert, "Pounds") == 0) || (strcmp(typeToConvert, "Pound") == 0) || (strcmp(typeToConvert, "Lbs") == 0) || (strcmp(typeToConvert, "Lb") == 0)) {
		memset(cupsInputAmountBuffer, 0, sizeof(cupsInputAmountBuffer));
		if (sum > 1)
			strcpy(cupsInputAmountBuffer, "%s Lbs", measurementAmount);
		else
			strcpy(cupsInputAmountBuffer, "%s Lb", measurementAmount);
		return;
	} else if ((strcmp(typeToConvert, "Grams") == 0) || (strcmp(typeToConvert, "Gram") == 0) || (strcmp(typeToConvert, "G") == 0) || (strcmp(typeToConvert, "Gs") == 0)) {
		memset(cupsInputAmountBuffer, 0, sizeof(cupsInputAmountBuffer));
		if (sum > 1)
			strcpy(cupsInputAmountBuffer, "%s Grams", measurementAmount);
		else
			strcpy(cupsInputAmountBuffer, "%s Gram", measurementAmount);
		return;
	} else 
	    return;
}