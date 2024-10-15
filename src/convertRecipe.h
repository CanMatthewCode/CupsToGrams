#ifndef CONVERTRECIPE_H
#define CONVERTRECIPE_H

#define MAX_INGREDIENT_NUMBER 60
#define MAX_INGREDIENT_TEXT 1000

enum recipeType{
	APPETIZER,
	BAKED_GOOD,
	BREAKFAST,
	DESSERT,
	MAINS,
	SIDES,
	SNACKS,
	SOUPS
};

struct ingredientStruct{
	char ingredientName[INGREDIENT_BUFFER_LEN];
	char userCupsInput[INGREDIENT_BUFFER_LEN];
	float ingredientGrams;
}

struct recipeStruct{
	struct ingredientStruct ingredients[MAX_INGREDIENT_NUMBER];
	int numberOfIngredients;
	char recipeDirections [MAX_INGREDIENT_NUMBER][MAX_INGREDIENT_TEXT];
	int numberOfDirections;
	char recipeNotes [MAX_INGREDIENT_NUMBER][MAX_INGREDIENT_TEXT];
	int numberOfNotes;
	enum recipeType type;
}

#endif //CONVERTRECIPE_H