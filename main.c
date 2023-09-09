#include "shell.h"

/**
 * main - Entry point for a simple shell program.
 *
 * @ac: The number of command-line arguments.
 * @av: An array of strings containing the command-line arguments.
 *
 * This function implements a simple shell that continuously reads input
 * from the user, processes it, and executes commands in child processes.
 * It also handles memory allocation and deallocation for input and command
 * strings using getline and strSplit functions, respectively.
 *
 * Return: 0 on success, or an exit status code on failure.
 */
int main(int argc, char **argv, char **env)
{
	char *input = NULL;
	size_t input_len = 0;
	char **command = NULL;
	int numStrings, status;
	pid_t child;

	(void)argc;

	while (1)
	{
		/*printCurrentWorkingDirectory();*/
		printf("$ ");
		if (getline(&input, &input_len, stdin) == -1)
			break;
		command = splitString(input, &numStrings);
		if (command[0] == NULL)
			continue;

		int result = executedcommand(command);
		if (result == 0)
			continue;
		else if (result == 1)
			continue;

		child = fork();
		if (child < 0)
			exit(1);
		if (child == 0 && command[0] != NULL && command != NULL)
		{
			if (execve(command[0], command, env) == -1)
			{
				perror(argv[0]);
				freeArray(command, numStrings);
				exit(0);
			}
		}
		else
		{
			waitpid(child, &status, 0);
			freeArray(command, numStrings);
		}
	}
	free(input);
	return 0;
}

int executedcommand(char **command)
{
	if (strcmp(command[0], "exit") == 0)
	{
		_print_str("Disconnected...\n");
		exit(0);
	}

	if (strcmp(command[0], "clear") == 0)
	{
		_print_str("\033[H\033[J");
		return 1;
	}

	if (strcmp(command[0], "mkdir") == 0)
	{
		if (mkdir(command[1], 0777) == -1)
		{
			perror("mkdir");
			return 1;
		}
		return 0;
	}

	if (strcmp(command[0], "cd") == 0)
	{
		if (command[1] == NULL)
		{
			perror("cd: missing argument\n");
			return 1;
		}

		if (!changeDirectory(command[1]))
		{
			perror("chdir");
			return 1;
		}

		return 1;
	}

	return excecuteoneCmd(command);
}

void printCurrentWorkingDirectory()
{
	char *buf;
	size_t size;

	size = pathconf(".", _PC_PATH_MAX);

	if ((buf = (char *)malloc((size_t)size)) != NULL)
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

int changeDirectory(const char *path)
{
	if (path == NULL)
	{
		perror("chdir: missing path\n");
		return 0;
	}

	if (chdir(path) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
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

int excecuteoneCmd(char **command)
{

	pid_t child = fork();
	if (child < 0)
	{
		perror("fork");
		return 0;
	}
	else if (child == 0)
	{

		char *lsArgs[] = {str_concat("/bin/", command[0]), command[1], NULL};
		char *lsEnv[] = {NULL};

		execve(str_concat("/bin/", command[0]), lsArgs, lsEnv);
		perror("execve");
		exit(1);
	}
	else
	{

		int status;
		waitpid(child, &status, 0);
		return 1;
	}

	return 2;
}