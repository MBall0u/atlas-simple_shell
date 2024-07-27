#ifndef main_h
#define main_h

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char **get_tokens(char *buf, char *sep);
char *path_get(char **env);
char *check_build(char *arg, char **path);

#endif
