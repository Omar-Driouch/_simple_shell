#include "shell.h"


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
