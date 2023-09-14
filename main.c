#include "shel.h"
#include <signal.h>

void sigint_handler()
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n$ ", 3);
}

int main(int ac, char **argv)
{
	char *line = NULL;
	char **command = NULL;
	int status = 0, tokens = 0;
	int l = 1, exi = 127;
	 

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{

		return 1;
	}

	(void)ac;
	while (l)
	{

		status = read_line(&line);
		l++;
		if (!line)
		{
			if (tokens == -1)
				exit(exi);
			exit(status);
		}
		if (!processLine(status, &line))
			continue;
		status = tokenizer(&line, &tokens, command, argv, environ, &l, &exi, &status);
		 
		if (!command && line == NULL)
		{
			free_2d_array(command);
			continue;
		}
		 
		if (status == 1)
		{
			free_2d_array(command);
			continue;
		}
		 

	}

	exit(0);
}