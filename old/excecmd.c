#include "shell.h"

/**
 * executedcommand - Execute a shell command based on the input.
 *
 * @command: An array of strings containing the command and its arguments.
 *
 * This function takes a command as an input and executes it. It handles
 * built-in commands like "exit," "clear," "mkdir," and "cd." For other
 * commands, it delegates the execution to the executeoneCmd function.
 *
 * Return: 0 for success, 1 for failure, or the result from executeoneCmd.
 */

int executedcommand(char **command, int *let)
{
	if (strcmp(command[0], "exit") == 0)
	{
		_print_str("Disconnected...\n");
		exit(0);
	}
	if (strcmp(command[0], "clear") == 0)
	{
		_print_str("\033[H\033[J");
		return (1);
	}
	if (strcmp(command[0], "mkdir") == 0)
	{
		if (mkdir(command[1], 0777) == -1)
		{
			perror("mkdir");
			return (1);
		}
		return (0);
	}
	if (strcmp(command[0], "cd") == 0)
	{
		if (command[1] == NULL)
		{
			perror("cd: missing argument\n");
			return (1);
		}
		if (!changeDirectory(command[1]))
		{
			perror("chdir");
			return (1);
		}
		return (1);
	}
	return (excecuteoneCmd(command, let));
}

void printCurrentWorkingDirectory(void)
{
	char *buf;
	size_t size;

	size = pathconf(".", _PC_PATH_MAX);
	buf = (char *)malloc((size_t)size);
	if (buf != NULL)
	{
		if (getcwd(buf, (size_t)size) != NULL)
		{
			_print_str(buf);
		}
		else
		{
			perror("getcwd");
		}
		free(buf);
	}
	else
	{
		perror("malloc");
	}
}

int changeDirectory(char *path)
{
	if (path == NULL)
	{
		perror("chdir: missing path\n");
		return (0);
	}

	if (chdir(path) == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
	free(path);
}

void _print_str(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int excecuteoneCmd(char **command, int *let)
{
	pid_t child = fork();
	int status;

	if (child < 0)
	{
		return (0);
	}
	else if (child == 0)
	{
		if (hasSubstring(command[0]) == 0)
		{
			command[0] = str_concat("/bin/", command[0]);
		}
		execve(command[0], command, NULL);
		handleCommandNotFound(command[0]);
		freeArray(command, *let);
		exit(1);
	}
	else
	{
		waitpid(child, &status, 0);
		freeArray(command, *let);
		return (1);
	}
	freeArray(command, *let);
	return (2);
}

/**
 * _strlen - returns length of string
 * @s: string
 * Return: length of string
 */

int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void handleCommandNotFound(char *command)
{
	char *not_found = ": 1: not found\n";
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, not_found, _strlen(not_found));
}