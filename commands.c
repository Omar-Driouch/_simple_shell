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
	temp = _strdup(*line);
	if (!temp)
	{
		*tokens = 0;
		return (NULL);
	}
	token = strtok(temp, " \t\n");
	while (token)
	{
		if (_strcmp(token, "#") == 0 && cpt != 0)
		{
			break;
		}
		
		cpt++;
		token = strtok(NULL, " \t\n");
	}
	*tokens = cpt;
	commands = (char **)malloc(sizeof(char *) * (cpt + 1));
	if (!commands)
	{
		free(temp);
		return (NULL);
	}
	token = strtok(*line, " \t\n");
	while (token)
	{
		if (_strcmp(token, "#") == 0 && i != 0)
		{
			break;
		}
		commands[i] = _strdup(token);
		token = strtok(NULL, " \t\n");
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
	char *error = removeBin(cmd[0]);
	write(STDERR_FILENO, arg[0], _strlen(arg[0]));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, error, _strlen(error));
	write(STDERR_FILENO, error_message, _strlen(error_message));
	write(STDERR_FILENO, "\n", 1);
}

int executCMD(char **command, char **argv, char **envi, int **numstr, int cd)
{
	pid_t child = -1;
	int status = 0;

	(void)argv;

	if (cd == -1 || cd == 1 || cd == 0)
	{
		if (cd == 0)
			handleError_cd_(argv,command); 
		**numstr = -1;
		return (-2);
	}
	
	if (hasSubstring(command[0]) == 0)
	{
		command[0] = str_concat("/bin/", command[0]);
	}

	if (pathExists(command[0]))
	{
		child = fork();

		if (child == 0 && command[0] != NULL)
		{
			if (execve(command[0], command, envi) == -1)
			{
				free_2d_array(command);
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		HndleErrorCmdNotfound(argv, command);
		**numstr = -1;
		return (-2);
	}

	if (child != 0)
	{
		waitpid(child, &status, 0);
	}
	free_2d_array(command);
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

int pathExists(char *path)
{

	if (access(path, F_OK) == 0)
	{

		return 1;
	}
	else
	{

		return 0;
	}
}



void handleError_cd_(char **argv, char **cmd)
{
	char error_message[] = ": can't cd to ";
	char *error = cmd[0];
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, error, _strlen(error));
	write(STDERR_FILENO, error_message, _strlen(error_message));
	write(STDERR_FILENO, cmd[1], _strlen(cmd[1]));
	write(STDERR_FILENO, "\n", 1);

}