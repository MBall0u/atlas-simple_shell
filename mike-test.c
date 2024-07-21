#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(void)
{
	char *sep = "\n ", *buf, *word;
	size_t size = 64;
	pid_t cmd;
	int status, count = 0;
	ssize_t check;
	char **args;

	buf = malloc(size);
	if (!buf)
	{
		return (1);
	}
	args = malloc(sizeof(char *) * size);
	if (!args)
	{
		return (1);
	}

	while (1)
	{
		printf("$ ");

		check = getline(&buf, &size, stdin);
		if (check == -1)
		{
			printf("Something went wrong!\n");
			break;
		}

		for (word = strtok(buf, sep); word != NULL; word = strtok(NULL, sep))
		{
			args[count] = word;
			count++;
		}

		cmd = fork();
		if (cmd == 0)
		{
			check = execve(args[0], args, NULL);
			if (check == -1)
			{
				return (1);
			}
		}
		else
		{
			check = waitpid(cmd, &status, 0);
			if (check == -1)
			{
				return (1);
			}
		}
	}
	free(buf);
	free(args);
	buf = NULL;
	return (0);
}
