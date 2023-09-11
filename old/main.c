#include "shell.h"

/**
 * main - Entry point for a simple shell program.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 * @env: env.
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
	int numStrings, status, result;
	pid_t child;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		printf("$ ");
		if (getline(&input, &input_len, stdin) == -1)
			break;
		command = splitString(input, &numStrings);
		if (command[0] == NULL)
			continue;
		result = executedcommand(command, &numStrings);
		if (result == 0)
			continue;
		else if (result == 1)
			continue;
		
		
		
		freeArray(command, numStrings);
		
	}
	free(input);
	return (0);
}

int hasSubstring(char *str)
{
	char *substring = "/bin/";
	int str_length = _strlen(str);
	int sub_length = _strlen(substring), i, j, found;

	for (i = 0; i <= str_length - sub_length; i++)
	{
		found = 1;
		for (j = 0; j < sub_length; j++)
		{
			if (str[i + j] != substring[j])
			{
				found = 0;
				break;
			}
		}
		if (found)
		{
			return (1);
		}
	}
	
	return (0);
}