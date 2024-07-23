#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(void)
{
	char *sep = "\n ", *word, *str; /*sep is the separators used for strtok, word is for the token, and str is for a dynamic version of buf*/
	size_t size = 64; /*size is a general buffer amount, but it is only being used for getline and it is actually being ignored because buf is NULL*/
	pid_t cmd; /*this holds the pid when fork is called so the two instances can run as needed*/
	int status, count; /*status is for the waitpid function and checks when the child process terminates, and count is used for how many tokens there are and uses that to dynamically allocate an array on char pointers*/
	ssize_t check; /*takes the return value of each function and checks for errors*/
	char **args; /*args is used for an array of char pointer to be dynamically allocated*/
	char *buf = NULL; /*buf is for getline to dynamically alloced inside the function, when buf is NULL the bufsize is ignored*/
	extern char **environ;
	char *temp = "/bin/";

	while (1)
	{
		printf("$ "); /*with print at the beginning of each line no matter what*/

		count = 0; /*initializes the count to zero for when it loops*/
		check = getline(&buf, &size, stdin); /*get input from standard input and dynamically allocates the needed memory to buf, ignoring size*/
		if (check == -1) /*check to see if getline failed*/
		{
			printf("Something went wrong!\n");
			break;
		}
		str = malloc(sizeof(char) * (strlen(buf) + 1)); /*allocated memory to str for the exact amount of buf + 1 for a null byte*/
		if (!str) /*checks to see if memory allocation failed*/
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		strcpy(str, buf); /*this step is needed because a we cannot pass a string literal through strtok because it cannot be modified*/

		for (word = strtok(str, sep); word != NULL; word = strtok(NULL, sep)) /*this step is to see how many tokens there are*/
		{
			count++;
		}

		args = malloc(sizeof(char *) * count); /*this uses count to dynamically alloced the exact amount of memory needed*/
		if (!args) /*checks if the memory allocation fails for args*/
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}

		count = 0; /*resets the count for adding the tokens to the args array*/
		for (word = strtok(str, sep); word != NULL; word = strtok(NULL, sep)) /*iterates through the string until token is NULL*/
		{
			args[count] = word; /*initializes the space in args to the current token*/
			count++; /*moves forward in args*/
		}

		cmd = fork(); /*creates a child process and stored the pid in cmd*/
		if (cmd == 0) /*check if this is the child process*/
		{
			strcat(temp, args[0]);
			args[0] = temp;
			check = execve(args[0], args, environ); /*executes program and stores the return value if there is one*/
			if (check == -1) /*checks if there was an error while executing*/
			{
				perror("Execve Error");
				exit(EXIT_FAILURE);
			}
		}
		else if (cmd == -1) /* -1 is failure*/
		{
			perror("fork failure");
			exit(EXIT_FAILURE);
		}
		else /*if not a child then a parent*/
		{
			check = waitpid(cmd, &status, 0); /*waits on the child process to terminate*/
			if (check == -1) /*checks if there was an error*/
			{
				perror("Error");
				exit(EXIT_FAILURE);
			}
		}
		free(str); /*frees dynamically allocated memory for str*/
		str = NULL;

		free(args); /*frees dynamically allocated memory for args*/
		args = NULL;
	}
	return (0);
}
