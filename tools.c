#include "shel.h"

int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
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

void _print_str(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

void exit_(char **cmd, int l)
{
	int status = 0;
	char error_message[] = "./hsh: 1: exit: Illegal number: ";

	if (cmd[1] != NULL)
	{
		if (atoi(cmd[1]) < 0 || _strcmp(cmd[1], "HBTN") == 0)
		{
			write(STDERR_FILENO, error_message, strlen(error_message));
			write(STDERR_FILENO, cmd[1], _strlen(cmd[1]));
			write(STDERR_FILENO, "\n", 1);
			status = 2;
		}
		if (atoi(cmd[1]) > 98)
			status = 232;
		else if (atoi(cmd[1]) > 0)
			status = atoi(cmd[1]);
		if (atoi(cmd[1]) == 0 && cmd[1] != NULL)
			status = -1;
	}
	if (l > 2)
	{
		free_2d_array(cmd);
		exit(2);
	}

	if (status != -1)
	{
		free_2d_array(cmd);
		exit(status);
	}
	else
	{
		free_2d_array(cmd);
		exit(2);
	}
}

int executecommand(char **cmd, char **ar, char **env, int *tok, int *l)
{

	if (strcmp(cmd[0], "exit") == 0)
	{
		exit_(cmd, *l);
		return (1);
	}
	if (strcmp(cmd[0], "clear") == 0)
	{
		_print_str("\033[H\033[J");
	}
	if (strcmp(cmd[0], "mkdir") == 0)
	{
		if (mkdir(cmd[1], 0777) == -1)
			perror(cmd[0]);
		return (1);
	}
	if (strcmp(cmd[0], "cd") == 0)
	{
		if (cmd[1] == NULL)
			_print_str("cd: missing argument\n");
		if (_strcmp(cmd[1], "-") == 0)
			path();
		if (!changeDirectory(cmd[1]))
			perror(ar[0]);
		return (1);
	}
	
	return (executCMD(cmd, ar, env, &tok));
}


