#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

static int max_args = 64; /*limit to amount of args*/

int main(void)
{
    char *line = NULL; /*buffer holding input*/
    size_t len = 0; /*length of buffer*/
    ssize_t read; /*hold the result of getline*/
    static int welcome = 0; /*used just to display welcome message once*/
    int i = 0; /*iterator for loop*/
    char *token; /*to hold tokens*/
    char *args[max_args]; /*to hold args, max args declared to 64*/
    int status; /*hold wait status*/
    pid_t pid; /*hold pid of child*/
	char *path = NULL; /*store a path*/
	char *envp[] = {"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", NULL};
	/*environment path is path variables to search*/

    if (welcome == 0) /*just the welcome message, change this later. set to 0 and will change value to display only once*/
    {
        printf("Welcome to Super Cool Guy Shell!\n");
        printf("Type help for commands, or type exit to quit. or cntrl d to quit.\n");
        welcome = 1; /*since it = 1 now it won't display again*/
        sleep(2); /*for dramatic effect*/
		printf("Super Cool Guy$ "); /*prompt message, random for now*/
    }

    while ((read = getline(&line, &len, stdin)) != -1) /*read user input here, and start the infinite loop*/
    {
        printf("Super Cool Guy$ "); /*prompt message, random for now*/
        token = strtok(line, " \t\r\n:a;"); /*turn line into tokens, not sure about delimeters used*/

        while (token != NULL && i < max_args) /*continue through all args, i is set to 0*/
		{
            args[i] = token; /*stores each word into i position of array*/
            token = strtok(NULL, " \t\r\n:a;"); /*adds a NULL and then moves to next delimeter*/
            i++; /*increment to next element of array*/
        }
        args[i] = NULL; /*add a NULL to the end of array*/

        if (args[0] == NULL) /*if first element is empty*/
		{
			/*do nothing and skip to next statement?*/
        }
		else if (strcmp(args[0], "exit") == 0) /*if they typed exit this will exit*/
		{
            printf("\nExiting Super Cool Guy Shell...\n\n"); /*dumb message to change*/
            free(line); /*free memory of lin*/
            return EXIT_SUCCESS;
        }
		else if (strcmp(args[0], "help") == 0) /*help messages to use later on*/
		{
            printf("Commands that work:\n");
            printf("ls: list files in current directory\n");
            printf("exit: quits program\n");
            printf("help: prints this help sequence again\n");
        }
		else /*if the word typed was not help or exit*/
		{
            pid = fork(); /*fork here*/

            if (pid == -1) /* -1 is failure*/
			{
                perror("fork failure");
                exit(EXIT_FAILURE);
            }
			else if (pid > 0) /*child is 0, so this is for parent to wait*/
			{
                waitpid(pid, &status, 0); /*store status until 0 "the child" is done*/
                fflush(stdout); /*put the output immediately rather than waiting for buffer*/
            }
			else /*child checks args*/
			{
                if (strncmp(args[0], "./", 2) == 0) /*trying to execute using ./ comparing only the first 2 characters */
				{
                    args[0] += 2; /*move forward 2 characters to skip ./ removing it*/
                    strcat(args[0], "/"); /* add / to continue path if its in a different directory*/
                }

                if (strcmp(args[0], "ls") == 0) /*direct path to ls*/
				{
                    path = "usr/bin/ls";
                }
				else if (strcmp(args[0], "cat") == 0) /*tried to do cat but doesn't work*/
				{
                    path = "/bin/cat";
                }
				else /*if command not found*/
				{
                    fprintf(stderr, "Unknown command: %s\n", args[0]);
                    exit(EXIT_FAILURE);
                }
                if (execve(path, args, envp) == -1) /*try to execute with envp */
				{
                    perror("execve failure");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    if (line != NULL) /*free line memory if there is something still there*/
	{
        free(line);
    }

    return EXIT_SUCCESS; /*return for succesful exit*/

}
