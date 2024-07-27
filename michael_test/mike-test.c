#include "main.h"
int main(void)
{
	char *sep = " \t\r\n:;="; /*sep is the separators used for strtok, word is for the token, and str is for a dynamic version of buf*/
	size_t size = 64; /*size is a general buffer amount, but it is only being used for getline and it is actually being ignored because buf is NULL*/
	pid_t cmd; /*this holds the pid when fork is called so the two instances can run as needed*/
	int status; /*status is for the waitpid function and checks when the child process terminates, and count is used for how many tokens there are and uses that to dynamically allocate an array on char pointers*/
	ssize_t check; /*takes the return value of each function and checks for errors*/
	char **args, **path_args; /*args is used for an array of char pointer to be dynamically allocated*/
	char *buf = NULL; /*buf is for getline to dynamically alloced inside the function, when buf is NULL the bufsize is ignored*/
	extern char **environ;
	char *path;

	while (1)
	{
		printf("$ "); /*with print at the beginning of each line no matter what*/

		check = getline(&buf, &size, stdin); /*get input from standard input and dynamically allocates the needed memory to buf, ignoring size*/
		if (check == -1) /*check to see if getline failed*/
		{
			buf = NULL;
			break;
		}

		args = get_tokens(buf, sep); /*makes an array of args from the string buf from getline*/
		path = path_get(environ); /*gets the path from the environment*/
		path_args = get_tokens(path, sep); /*makes an array of args from the path returned from the above function*/
		args[0] = check_build(args[0], path_args); /*gets a workable path and puts it in postion 0 of the args array*/
		if (args[0] == NULL)
		{
			perror("Cannot find command");
			exit(EXIT_FAILURE);
		}

		cmd = fork(); /*creates a child process and stored the pid in cmd*/
		if (cmd == 0) /*check if this is the child process*/
		{
			printf("%s\n", args[0]);
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
		free(buf); /*frees dynamically allocated memory for str*/
		buf = NULL;
		free(args); /*frees dynamically allocated memory for args*/
		args = NULL;
		free(path_args);
		path_args = NULL;
	}
	return (0);
}
