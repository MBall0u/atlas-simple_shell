#include "main.h"
/**
 * 
 * 
 * 
*/
void free_all(char ***args, char ***path_args, char **buf, char **temp)
{
	int i;

	free(*buf); /*frees dynamically allocated memory for str*/
	*buf = NULL;
	for (i = 0; (*args)[i] != NULL; i++)
	{
		free((*args)[i]);
	}
	free(*args); /*frees dynamically allocated memory for args*/
	*args = NULL;
	free(*path_args);
	*path_args = NULL;
	free(*temp);
	*temp = NULL;
}
