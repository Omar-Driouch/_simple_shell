#include "shel.h"

int read_line(char **line)
{
	size_t len = 0;
	int n = 0;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	n = getline(line, &len, stdin);

	if (n == -1)
	{
		free(*line);
		*line = NULL;
		return (0);
	}

	if (n > 0 && (*line)[n - 1] == '\n')
		(*line)[n - 1] = '\0';

	return (isWhitespaceString(*line));
}

char **tokenizer(char **line, int *tokens)
{
	char *token = NULL, *temp = NULL;
	char **commands = NULL;
	int cpt = 0, i = 0;

	if (!*line || !*line[0] || _strcmp(*line, "\n") == 0)
	{
		*tokens = 0;
		return (NULL);
	}
	temp = strdup(*line);
	if (!temp)
	{
		*tokens = 0;
		return (NULL);
	}
	token = strtok(temp, " \t\n&&;");
	while (token)
	{
		cpt++;
		token = strtok(NULL, " \t\n&&;||");
	}
	*tokens = cpt;
	commands = (char **)malloc(sizeof(char *) * (cpt + 1));
	if (!commands)
	{
		free(temp);
		return (NULL);
	}
	token = strtok(*line, " \t\n&&;||");
	while (token)
	{
		commands[i] = _strdup(token);
		token = strtok(NULL, " \t\n&&;||");
		i++;
	}
	free(temp);
	free(*line);
	*line = NULL;
	commands[i] = NULL;
	return (commands);
}

char *removeBin(char *input)
{
	char *start = input;
	char substring[] = "/bin/";
	char *source = input;
	int match = 0;

	while (*source)
	{
		if (*source == substring[match])
		{
			match++;
			source++;
			if (substring[match] == '\0')
			{
				match = 0;
			}
		}
		else
		{
			*start = *source;
			start++;
			source++;
			match = 0;
		}
	}

	*start = '\0';

	if (*input)
	{
		return input;
	}
	else
	{
		return NULL;
	}
}

void HndleErrorCmdNotfound(char **arg, char **cmd)
{
	char error_message[] = ": not found";
	write(STDERR_FILENO, arg[0], _strlen(arg[0]));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, removeBin(cmd[0]), _strlen(removeBin(cmd[0])));
	write(STDERR_FILENO, error_message, _strlen(error_message));
	write(STDERR_FILENO, "\n", 1);
	 
}

int executCMD(char **command, char **argv, char **envi, int numstr)
{
	pid_t child = -1;
	int status = 0;

	(void)numstr;
	(void)argv;
	child = fork();
	if (child == 0 && command[0] != NULL)
	{
		if (hasSubstring(command[0]) == 0)
		{
			command[0] = str_concat("/bin/", command[0]);
		}

		if (execve(command[0], command, envi) == -1)
		{
			HndleErrorCmdNotfound(argv, command);
			
			return (-2);
		}
	}
	else
	{
		waitpid(child, &status, 0);
		free_2d_array(command);
	}

	return (WEXITSTATUS(status));
}

int isWhitespaceString(char *str)
{
	int i;
	if (str == NULL)
		return (0);

	for (i = 0; str[i] != '\0'; i++)
	{

		if (!_isspace((unsigned char)str[i]))
			return (5);
	}

	return (1);
}

int processLine(int status, char **line)
{
	if ((status == 0 || status == 1) && (*line[0] == '\0'))
	{
		free(*line);
		return (0);
	}
	if (status == 1)
	{
		free(*line);
		return (0);
	}
	return (1);
}
