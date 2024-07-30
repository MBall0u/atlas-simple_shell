#include "main.h"
/**
 * check_build - looks to see if the inputted command is a built-in
 * Description - takes in the arg[0] of the line input
 * then checks and sees if the straight input is a valid path,
 * if not then it starts working through the path tokens to see if
 * it can find a valid path
 * @arg: the passed arg[0] from the getline tokens
 * @path: the path tokens
 * Return: valid path for built-in command (success)
*/
char *check_build(char *arg, char **path)
{
	struct stat st; /*the file info*/
	char *temp = NULL; /*a temp string for the path arg and the input to get spliced*/
	int count = 1; /*arg position counter*/

	if (stat(arg, &st) == 0) /*checks to see if the base argument is a valid path first*/
	{
		return (arg); /*if it is then it returns that to the calling function*/
	}
	else /*argument is not a valid path*/
	{
		while (path[count] != NULL) /*loop that iterates through the passed path args*/
		{
			temp = malloc(sizeof(char) * (strlen(path[count]) + 2 + (strlen(arg))));
			strcpy(temp, path[count]);
			strcat(temp, "/");
			strcat(temp, arg); /*adds the arg to the back of the path*/
			if (stat(temp, &st) == 0) /*checks to see if new path is valid*/
			{
				if (access(temp, X_OK) == 0)
				{
					return (temp); /*if it is valid then it returns to the calling function with the new path*/
				}
			}
			count++; /*if that path is not valid then it goes to the next path arg*/
		}
	}
	return (NULL); /*if it goes through all path args and still does not find a valid path it returns NULL*/
}
