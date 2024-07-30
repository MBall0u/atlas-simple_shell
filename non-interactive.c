#include "main.h"
/**
 * 
 * 
 * 
*/
int non_interactive(void)
{
	char *sep = " \t\r\n:;="; /*sep is the separators used for strtok, word is for the token, and str is for a dynamic version of buf*/
	size_t size = 64; /*size is a general buffer amount, but it is only being used for getline and it is actually being ignored because buf is NULL*/
	ssize_t check;
	char **args, **path_args; /*args is used for an array of char pointer to be dynamically allocated*/
	char *buf = NULL; /*buf is for getline to dynamically alloced inside the function, when buf is NULL the bufsize is ignored*/
	extern char **environ;
	char *path, *temp = NULL;

	check = getline(&buf, &size, stdin); /*get input from standard input and dynamically allocates the needed memory to buf, ignoring size*/
	if (check == -1) /*check to see if getline failed*/
	{
		buf = NULL;
		exit(EXIT_FAILURE);
	}

	args = get_tokens(buf, sep); /*makes an array of args from the string buf from getline*/
	path = path_get(environ); /*gets the path from the environment*/
	path_args = get_tokens(path, sep); /*makes an array of args from the path returned from the above function*/
	temp = check_build(args[0], path_args); /*gets a workable path and puts it in postion 0 of the args array*/
	if (temp == NULL)
	{
		perror("Cannot find command\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		args[0] = temp;
		function_call(args, environ);
	}
	free_all(&args, &path_args, &buf, &temp);
	return (0);
}
