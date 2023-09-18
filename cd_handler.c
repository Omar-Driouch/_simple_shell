#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cd_command(int tokens, char **command)
{
	char *prev_dir = my_getenv("OLDPWD");
	char *cwd = getcwd(NULL, 0), *home_dir;

	if (tokens == 1 || (tokens == 2 && strcmp(command[1], "~") == 0))
	{
		home_dir = my_getenv("HOME");
		if (!home_dir)
			home_dir = my_getenv("PWD");
		if (chdir(home_dir) == 0)
		{
			set_variable_env("OLDPWD", cwd);
			return (1);
		}
	}
	else if (tokens == 2 && strcmp(command[1], "-") == 0)
	{
		if (prev_dir && chdir(prev_dir) == 0)
		{
			_print_str(prev_dir);
			_print_str("\n");
			set_variable_env("OLDPWD", cwd);
			free(cwd);
			return (1);
		}
	}
	else if (tokens == 2)
	{
		if (chdir(command[1]) == 0)
		{
			set_variable_env("OLDPWD", cwd);
			free(cwd);
			return (1);
		}
	}
	free(cwd);
	return (0);
}

char *my_getenv(const char *name)
{
	size_t name_len = strlen(name);
	char *result = NULL;
	char **env = environ;

	if (name == NULL || environ == NULL)
	{
		return (NULL);
	}

	while (*env != NULL)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			result = &(*env)[name_len + 1];
			break;
		}
		env++;
	}

	return (result);
}

int set_variable_env(char *name, char *new_value)
{
	size_t name_len = strlen(name);

	char **env = environ;
	int check = 0;

	if (name == NULL || environ == NULL)
	{
		return (0);
	}

	while (*env != NULL)
	{
		if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{

			check = 1;
			_strcpy(*env, "OLDPWD=");
			*env = _concat_whitout_malloc(*env, new_value);

			break;
		}

		env++;
	}

	if (!check)
	{
		add_OLDPWD_to_env("PWD", new_value);
	}

	return (1);
}

int add_OLDPWD_to_env(char *name, char *new_value)
{
	size_t name_len = strlen(name);

	char **env = environ;
	int check = 0;
	(void)new_value;
	if (name == NULL || environ == NULL)
	{
		return (0);
	}

	while (*env != NULL)
	{
		if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{

			check = 1;
			strcpy(*env, "OLDPWD=");
			*env = _concat_whitout_malloc(*env, new_value);

			break;
		}

		env++;
	}
	if (!check)
	{
	}

	return (1);
}
