#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include "recipeSystemCheck.h"
#ifdef __APPLE__
	#include <mach-o/dyld.h>
#elif __linux__
	#include <unistd.h>
	#include <linux/limits.h>
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
	
	//remove exe name from pathway /recipeConverter by truncating at last \ or /
	#ifdef _WIN32
		char *lastSlash = strrchr(pathwayBuffer, '\\');
		if (lastSlash != NULL){
			*lastSlash = '\0';
	}
	#else
		char *lastSlash = strrchr(pathwayBuffer, '/');
		if (lastSlash != NULL){
			*lastSlash = '\0';
		}
	#endif
}
