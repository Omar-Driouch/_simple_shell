#include "shel.h"

int handle_commanets(char **cmd, int **ex)
{

	if (_strcmp(cmd[0], "#") == 0)
	{
		**ex = 0;

		return 1;
	}

	return (-2);
}