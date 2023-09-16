#ifndef SHEL_H
#define SHEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <aio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>
#include <signal.h>
#include <dirent.h>

extern char **environ;

int read_line(char **line);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *str_concat(char *s1, char *s2);
void freeArray(char **ptr, int numstrs);
int tokenizer(char **line, int *tokens, char **cmd, char **argv, char ** env, int *l, int *exi, int *status);

int executecmd(char **cmd, char **ar, char **en, int *tokns, int *l,int *ex);
int isWhitespaceString(char *str);
int processLine(int status, char **line);
int _isspace(char ch);

int executCMD(char **command, char **argv, char **env, int **tokens, int cd);

void printCurrentWorkingDirectory(void);
int changeDirectory(char *path);
void _print_str(char *str);
int hasSubstring(char *str);
int _strlen(char *s);
/* void handleCommandNotFound(char *command); */
void free_2d_array(char **array);
char * newpathh(void);

void exit_(char **cmd, int l);


void HndleErrorCmdNotfound(char **arg, char **cmd);
char *removeBin(char *input);
int pathExists(char *path);

char *_strcpy(char *dest, char *src);
void handleError_cd_(char **argv, char **cmd);
int handle_commanets(char **cmd, int **l);
char *get_Home_Dir(void);

int cd_command(int tokens, char **command);
char *my_getenv(const char *name);
void setenvir(void);
int set_variable_env(char *name, char *new_value);
char *_concat_whitout_free(char *s1, char *s2);
int _strncmp(char *str1,char *str2, size_t n);
void concat(char *s1, char *s2, char **env);

#endif
