#include "main.h"
char *check_build(char *arg, char **path)
{
	struct stat st;
	char *temp;

	if (stat(arg, &st) == 0)
	{
		return (arg);
	}
	else
	{
		while (*path != NULL)
		{
			temp = *path;
			strcat(arg, temp);
			if (stat(arg, &st) == 0)
			{
				return (arg);
			}
			path++;
		}
	}
	return (NULL);
}