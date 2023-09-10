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
int executedcommand(char **command, int *let);
char *str_concat(char *s1, char *s2);
void printCurrentWorkingDirectory();
int changeDirectory(char *path);
void _print_str(char *str);
int excecuteoneCmd(char **command, int *let);
int hasSubstring(char *str);
int _strlen(char *s);
void handleCommandNotFound(char *command);

#endif