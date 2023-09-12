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
			printf("command %s\n",command[0]);
			printf("%d\n",status);
			printf("%d\n",tokens);
			printf("%d\n",line);
			exit(0);
		}
		if (!processLine(status, &line))
			continue;
		command = tokenizer(&line, &tokens);
		if (!command && line == NULL)
		{
			free_2d_array(command);
			continue;
		}
		status = executecommand(command, argv, environ, tokens, &l);
		if (status == 1)
		{
			free_2d_array(command);
			continue;
		}
		if (status == -2)
		{
			free_2d_array(command);
			return (0);
		}
	}

	exit(0);
}
