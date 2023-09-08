#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <aio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char **splitString(char *input, int *numStrings);
void freeArray(char **ptr, int numStrings);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
#endif