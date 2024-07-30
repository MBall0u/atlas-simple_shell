#include "main.h"
/**
 * 
 * 
 * 
*/
void intermediate_free(char **buf, char ***args)
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
}