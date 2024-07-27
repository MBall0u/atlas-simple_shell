#include "main.h"
char **get_tokens(char *buf, char *sep)
{
	char *word, *str;
	char **args;
	char *temp_str;
	int count = 0;

	str = malloc(sizeof(char) * (strlen(buf) + 1));
	if (!str)
	{
		perror("Allocation Error");
		exit(EXIT_FAILURE);
	}
	strcpy(str, buf);
	temp_str = strdup(str);

	for (word = strtok(temp_str, sep); word != NULL; word = strtok(NULL, sep))
	{
		count++;
	}

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		perror("Allocation Error");
		exit(EXIT_FAILURE);
	}

	count = 0;
	for (word = strtok(str, sep); word != NULL; word = strtok(NULL, sep))
	{
		args[count] = word;
		count++;
	}
	args[count] = NULL;
	free(temp_str);
	temp_str = NULL;
	return (args);
}
