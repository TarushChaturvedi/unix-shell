#pragma once

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

/*
	Takes in the executable name and checks it using the PATH environment variable.
	If it exists then it returns the path of the file which is malloced, if not it returns NULL.

	Example:
	
	char file[] = "ls";
	char* file_path = find_in_path(file);
	if (file_path != NULL)
		execve(file, NULL, NULL);
	free(file_path);
*/
char* find_in_path(const char* filename);
