#include "main.h"
/**
 * get_tokens - takes a string and returns an array of char pointers
 * Description - takes an inputted string and makes a couple of copies
 * that can be modified, creates an array of char pointers, and returns it
 * @buf: the string literal that was acquired from getline
 * @sep: list of separators that will be used for strtok
 * Return: returns an array of char pointers (success)
*/
char **get_tokens(char *buf, char *sep)
{
	char *word, *str; /*word is the pointer used to iterate through strtok, str is a dynamically allocated string that can be modified by strtok*/
	char **args; /*an array of char pointers that will be dynamically allocated based off of strtok and then returned to the calling function*/
	char *temp_str; /*a temp string that is used to find out how large we need to make the arg list*/
	int count = 0; /*a count of how many args there are*/

	str = malloc(sizeof(char) * (strlen(buf) + 1)); /*dynamically allocating the memory for string*/
	if (!str)
	{
		perror("Allocation Error");
		exit(EXIT_FAILURE);
	}
	strcpy(str, buf); /*copies the buffer to the allocated string*/
	temp_str = strdup(str); /*creates a duplicate string for our count*/

	for (word = strtok(temp_str, sep); word != NULL; word = strtok(NULL, sep)) /*counts how many arguments there are*/
	{
		count++;
	}

	args = malloc(sizeof(char *) * (count + 1)); /*dynamically allocates an array of char pointers based off of the count*/
	if (!args)
	{
		perror("Allocation Error");
		exit(EXIT_FAILURE);
	}

	count = 0; /*count reset for arg initialization*/
	for (word = strtok(str, sep); word != NULL; word = strtok(NULL, sep)) /*initializes position count in the array of char pointers to the arg*/
	{
		args[count] = word;
		count++;
	}
	args[count] = NULL; /*sets the final position in the array to NULL*/
	free(temp_str); /*frees the memory allocated during the string duplication*/
	temp_str = NULL; /*sets it to NULL after being free'd*/
	return (args); /*returns the array of args to the calling function*/
}
