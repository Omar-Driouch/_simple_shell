#include "shel.h"




int main(int ac, char **argv)
{
	char *line = NULL;
	char **command = NULL;
	int status = 0, tokens = 0;
	int l = 1;
	 
	(void)ac;
	while (l)
	{

		status = read_line(&line);
		l++;
		if (!line)
		{
			if (tokens == -1)
				exit(127);
			exit(status);
		}
		if (!processLine(status, &line))
			continue;
		command = tokenizer(&line, &tokens);
		if (!command && line == NULL)
		{
			free_2d_array(command);
			continue;
		}
		status = executecommand(command, argv, environ, &tokens, &l);
		if (status == 1)
		{
		 
			free_2d_array(command);
			continue;
		}
		if (status == -2)
		{
			free_2d_array(command);
			continue;
		}
		 
		 
		
	}

	exit(0);
}