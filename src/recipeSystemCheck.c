#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include "recipeSystemCheck.h"
#ifdef __APPLE__
	#include <mach-o/dyld.h>
#elif __linux__
	#include <unistd.h>
#elif _WIN32
	#include <windows.h>
	#include <direct.h>
#else 
	#error "Unknown Platform"
#endif

char pathwayBuffer[PATH_MAX] = {'\0'};

/********************************************************************************************************************
* 																													*
*	  			function to fill pathwayBuffer with the pathway to the exe so as to find							*
*				needed .txt files to load in relative to the exe													*
*																													*
*********************************************************************************************************************/
void setExePath(){
	//get the correct platform dependent path to the exe
	#ifdef __APPLE__
		uint32_t size = sizeof(pathwayBuffer);
		_NSGetExecutablePath(pathwayBuffer, &size);
	#elif __linux__
		readlink("/proc/self/exe", pathwayBuffer, sizeof(pathwayBuffer));
	#elif _WIN32
		GetModuleFileName(NULL, pathwayBuffer, sizeof(pathwayBuffer));
	#else 
		#error "Unknown Platform"
	#endif
	
	//remove exe name from pathway /recipeConverter/recipeConverter
	#ifdef _WIN32
		if (strstr(pathwayBuffer, "\\recipeConverter\\recipeConverter.exe") != NULL){
		int pathwaySize = strlen(pathwayBuffer);
		for (int i = pathwaySize; i > pathwaySize - 19; i--) // 'recipeConverter.exe' is 19 char long
			pathwayBuffer[i] = '\0';
	}
	#else
		if (strstr(pathwayBuffer, "/recipeConverter/recipeConverter") != NULL){
		int pathwaySize = strlen(pathwayBuffer);
		for (int i = pathwaySize; i > pathwaySize - 16; i--) // 'recipeConverter' is 15 chars long
			pathwayBuffer[i] = '\0';
	}
	#endif
}
