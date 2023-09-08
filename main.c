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
		printf("$ ");
		if (getline(&input, &input_len, stdin) == -1)
			break;
		if (_strcmp(input, "exit") == 0)
		{
			printf("Disconnected...");
			break;
		}
		if (_strcmp(input, "clear") == 0)
		{
			system("clear");
			continue;
		}

		command = splitString(input, &numStrings);
		if (command[0] == NULL)
		{
			continue;
		}
		
		if (_strcmp(command[0], "mkdir") == 0)
		{
			if (mkdir(command[1], 0755) == -1)
			{
				perror("Error creating directory");
				return 1;
			}
			continue;
		}
		if (_strcmp(command[0], "cd") == 0)
		{
			if (chdir(command[1]) == -1)
			{
				perror("Error changing directory");
				return 1;
			}
			continue;
		}

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
