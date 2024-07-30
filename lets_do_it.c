#include "main.h"
/**
 * 
 * 
 * 
 * 
 * 
 * 
*/
void function_call(char **args, char **env)
{
	pid_t cmd;
	int status;
	ssize_t check;
	cmd = fork(); /*creates a child process and stored the pid in cmd*/
	if (cmd == 0) /*check if this is the child process*/
	{
		check = execve(args[0], args, env); /*executes program and stores the return value if there is one*/
		if (check == -1) /*checks if there was an error while executing*/
		{
			perror("Execve Error\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (cmd == -1) /* -1 is failure*/
	{
		perror("fork failure\n");
		exit(EXIT_FAILURE);
	}
	else /*if not a child then a parent*/
	{
		check = waitpid(cmd, &status, 0); /*waits on the child process to terminate*/
		if (check == -1) /*checks if there was an error*/
		{
			perror("Error\n");
			exit(EXIT_FAILURE);
		}
	}
}
