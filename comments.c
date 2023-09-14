#include "shel.h"


int  handle_commanets(char **cmd, int **ex)
{
	

	int i;

	if (_strcmp(cmd[0], "#") == 0)
	{
		**ex = 0;
		
		return 1;
		
	}
	for (i = 0; cmd[i]; i++)
	{
		/* if (_strcmp(cmd[i], "#") == 0)
		{
			**ex = 0;
			for (j = i; cmd[j]; j++)
			{
				free(cmd[i]);
				cmd[i] = NULL;
			}
			return -2;
			
			
			
		} */
	}
	 
	return (-2);
}