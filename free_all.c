#include "main.h"
/**
 * 
 * 
 * 
*/
void free_all(char ***args, char ***path_args, char **buf, char **temp)
{
	int i = 0;

	free(*buf); /*frees dynamically allocated memory for str*/
	*buf = NULL;
	for (i = 0; (*args)[i] != NULL; i++)
		free((*args)[i]);
	free(*args); /*frees dynamically allocated memory for args*/
	*args = NULL;
	if (*path_args != NULL)
	{
		for (i = 0; (*path_args)[i] != NULL; i++)
		{
			free((*path_args)[i]);
		}
	}
	free(*path_args);
	*path_args = NULL;
	if (*temp != NULL)
	{
		free(*temp);
		*temp = NULL;
	}
}
