#include "shell.h"

/**
 * executecmd - Execute a command with specified arguments.
 * @cmd: An array of strings representing the command and its arguments.
 * @ar: An array of strings representing the command-line arguments.
 * @env: An array of strings representing the environment variables.
 * @tok: A pointer to an integer representing the number of tokens.
 * @l: A pointer to an integer representing the current line number.
 * @ex: A pointer to an integer representing the exit status.
 *
 * Return: The result of executing the command.
 */
int executecmd(char **cmd, char **ar, char **env, int *tok, int *l, int *ex)
{
	int cd = -2;

	if (_strcmp(cmd[0], "exit") == 0)
	{
		exit_(cmd, *l);
		return (1);
	}
	if (_strcmp(cmd[0], "clear") == 0)
	{
		_print_str("\033[H\033[J");
	}
	if (_strcmp(cmd[0], "mkdir") == 0)
	{
		if (mkdir(cmd[1], 0777) == -1)
			perror(cmd[0]);
		cd = 1;
	}
	cd = handle_commanets(cmd, &ex);
	if (_strcmp(cmd[0], "cd") == 0)
	{

		if (cd_command(*tok, cmd))
		{
			cd = -1;
		}
		else
		{
			cd = 0;
		}
	}
	return (executCMD(cmd, ar, env, &tok, cd));
}

/**
 * get_Home_Dir - Retrieve the home directory of the current user.
 * Return: A pointer to a string representing the user's home directory, or
 * NULL if the home directory is not found or an error occurs.
 */
char *get_Home_Dir(void)
{
	const char *directory_path = "/home";
	DIR *dir;
	struct dirent *entry;

	char *homedir = NULL;

	dir = opendir(directory_path);
	if (dir == NULL)
	{

		return (homedir);
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_DIR)
		{
			if (_strcmp(entry->d_name, ".") != 0 && _strcmp(entry->d_name, "..") != 0)
			{
				homedir = entry->d_name;
			}
		}
	}

	closedir(dir);
	return (homedir);
}
