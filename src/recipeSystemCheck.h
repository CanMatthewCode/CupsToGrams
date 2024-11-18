#ifndef RECIPESYSTEMCHECK_H
#define RECIPESYSTEMCHECK_H

#include <stdio.h>
#include <limits.h>

extern char pathwayBuffer[PATH_MAX];

/********************************************************************************************************************
* 																													*
*	  			function to fill pathwayBuffer with the pathway to the exe so as to find							*
*				needed .txt files to load in relative to the exe													*
*																													*
*********************************************************************************************************************/
void setExePath();

#endif //RECIPESYSTEMCHECK_H
