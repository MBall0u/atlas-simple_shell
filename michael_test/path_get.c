#include "main.h"
char *path_get(char **env)
{
	char *temp;

	while (*env)
	{
		temp = *env;
		if (strncmp("PATH", temp, 4) == 0)
		{
			return (temp);
		}
		env++;
	}
	return (NULL);
}
