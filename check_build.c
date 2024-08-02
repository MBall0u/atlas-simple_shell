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
	int count, i; /*arg position counter*/
	char **temp_args;

	for (count = 0; path[count] != NULL; count++)
	{}
	temp_args = malloc(sizeof(char *) * (count + 1));
	if (!temp_args)
	{
		perror("Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	temp_args[count] = NULL;

	for (count = 0; path[count] != NULL; count++)
	{
		temp_args[count] = malloc(sizeof(char) * (strlen(path[count]) + strlen(arg) + 2));
		if (!temp_args[count])
		{
			perror("Allocation Error\n");
			exit(EXIT_FAILURE);
		}
		strcpy(temp_args[count], path[count]);
		strcat(temp_args[count], "/");
		strcat(temp_args[count], arg);
	}
	if (stat(arg, &st) == 0) /*checks to see if the base argument is a valid path first*/
	{
		for (i = 0; i <= count; i++)
			free(temp_args[i]);
		free(temp_args); /*frees dynamically allocated memory for args*/
		temp_args = NULL;
		return (arg); /*if it is then it returns that to the calling function*/
	}
	else /*argument is not a valid path*/
	{
		for (count = 1; temp_args[count] != NULL; ++count) /*loop that iterates through the passed path args*/
		{
			temp = strdup(temp_args[count]);
			if (stat(temp, &st) == 0 && access(temp, X_OK) == 0) /*checks to see if new path is valid*/
			{
				for (i = 0; i <= count; i++)
					free(temp_args[i]);
				free(temp_args); /*frees dynamically allocated memory for args*/
				temp_args = NULL;
				return (temp); /*if it is valid then it returns to the calling function with the new path*/
			}
			free(temp);
			temp = NULL;
		}
	}
	for (count = 0; temp_args[count] != NULL; count++)
		free(temp_args[count]);
	free(temp_args); /*frees dynamically allocated memory for args*/
	temp_args = NULL;
	return (NULL); /*if it goes through all path args and still does not find a valid path it returns NULL*/
}
