#include "shell.h"

/* int cd_command(int tokens, char **command)
{
	if (tokens == 1 || (tokens == 2 && strcmp(command[1], "~") == 0))
	{
		const char *home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			fprintf(stderr, "HOME environment variable not set.\n");
			return 0;
		}
		if (chdir(home_dir) != 0)
		{
			perror("cd");
			return 0;
		}
	}
	else if (tokens == 2 && strcmp(command[1], "-") == 0)
	{
		const char *prev_dir = getenv("OLDPWD");
		if (prev_dir == NULL)
		{

			return 0;
		}
		if (chdir(prev_dir) != 0)
		{

			return 0;
		}
	}
	else if (tokens == 2)
	{
		if (chdir(command[1]) != 0)
		{

			return 0;
		}
	}
	else
	{

		return 0;
	}

	return 1;
} */

int cd_command(int tokens, char **command)
{
	char *prev_dir = my_getenv("OLDPWD");

	if (prev_dir == NULL && tokens == 2 && strcmp(command[1], "-") == 0)
	{
		setenvir();

		prev_dir = my_getenv("OLDPWD");
		if (prev_dir)
		{
			_print_str(prev_dir);
			_print_str("\n");
		}

		return 1;
	}

	if (tokens == 1 || (tokens == 2 && strcmp(command[1], "~") == 0))
	{
		const char *home_dir = my_getenv("HOME");
		if (home_dir == NULL)
		{
			home_dir = my_getenv("OLDHOME");
			if (home_dir == NULL)
				return 0;
		}
		if (chdir(home_dir) != 0)
		{

			return 0;
		}
	}
	else if (tokens == 2 && strcmp(command[1], "-") == 0)
	{

		setenvir();
		if (chdir(prev_dir) != 0)
		{

			return 0;
		}
		_print_str(prev_dir);
		_print_str("\n");
	}
	else if (tokens == 2)
	{
		setenvir();
		if (chdir(command[1]) != 0)
		{
			return 0;
		}
	}
	else
	{

		return 0;
	}

	return 1;
}

char *my_getenv(const char *name)
{
	size_t name_len = strlen(name);
	char *result = NULL;
	char **env = environ;
	if (name == NULL || environ == NULL)
	{
		return NULL;
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

void setenvir(void)
{
	char *cwd = getcwd(NULL, 0);

	if (cwd != NULL)
	{

		setenv("OLDPWD", cwd,1);
		free(cwd);
	}
}

int set_variable_env(char *name, char *new_value)
{
	size_t name_len = strlen(name);
	/* char *newVar; */

	char **env = environ;

	if (name == NULL || environ == NULL)
	{
		return 0;
	}

	while (*env != NULL)
	{
		if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{

			/* 			newVar = _concat_whitout_free("OLDPWD=", new_value);

						*env = newVar; */

			concat("OLDPWD=", new_value, &*env);

			break;
		}

		env++;
	}

	return (1);
}

/* void concat(char *s1, char *s2, char **env)
{

	size_t s1_len = strlen(s1);
	size_t s2_len = strlen(s2);
	size_t total_len = s1_len + s2_len;
	size_t i;

	*env = (char *)malloc(total_len + 1);

	if (*env == NULL) {

		exit(1);
	}

	for ( i = 0; i < s1_len; i++) {
		(*env)[i] = s1[i];
	}

	for ( i = 0; i < s2_len; i++) {
		(*env)[s1_len + i] = s2[i];
	}

	(*env)[total_len] = '\0';





} */

void concat(char *s1, char *s2, char **env)
{
	size_t s1_len = strlen(s1);
	size_t s2_len = strlen(s2);
	size_t total_len = s1_len + s2_len;
	size_t i;

	for ( i = 0; i < s2_len; i++)
	{
		(*env)[s1_len + i] = s2[i];
	}

	(env)[total_len] = '\0';
}
