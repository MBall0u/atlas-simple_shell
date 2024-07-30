#include "main.h"
/**
 * path_get - gets the path for the environment
 * Description - gets the variable environ, which is an array of
 * char pointers, passed to it and iterates through it until it
 * finds the path pointer
 * @env: an environment pointer
 * Return: pointer to the PATH line in the environment
*/
char *path_get(char **env)
{
	char *temp; /*string pointer that will be compared*/

	while (*env) /*while env != NULL*/
	{
		temp = *env; /*sets temp to the environment pointer*/
		if (strncmp("PATH", temp, 4) == 0) /*checks to see if it is the PATH*/
		{
			return (temp); /*returns a pointer to the PATH if so*/
		}
		env++; /*if not it iterates to the next point in the array of char pointers*/
	}
	return (NULL); /*shouldn't not find it but if it does then this will return NULL*/
}
