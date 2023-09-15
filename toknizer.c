#include "shell.h"

int tokenizer(char **line, int *tokens, char **commands,
			  char **argv, char **env, int *l, int *exi, int *status)
{
	char *token = NULL, *temp = NULL;
	int cpt = 0, i = 0;
	
	if (!*line || !*line[0] || _strcmp(*line, "\n") == 0)
	{
		*tokens = 0;
		return (0);
	}
	temp = _strdup(*line);
	if (!temp)
	{
		*tokens = 0;
		return (0);
	}
	token = strtok(temp, " \t\n\r\a");
	while (token)
	{
		if (_strcmp(token, "#") == 0 && cpt != 0)
			break;
		cpt++;
		token = strtok(NULL, " \t\n\r\a");
	}
	*tokens = cpt;
	commands = (char **)malloc(sizeof(char *) * (cpt + 1));
	if (!commands)
	{
		free(temp);
		return (0);
	}
	token = strtok(*line, " \t\n\r\a");
	while (token)
	{
		if (_strcmp(token, "#") == 0 && i != 0)
			break;
		if (_strcmp(token, ";") == 0 && i != 0)
			return 0;
		commands[i] = _strdup(token);
		token = strtok(NULL, " \t\n\r\a");
		i++;
	}
	free(temp),free(*line);
	*line = NULL;
	commands[i] = NULL;
	*status = executecmd(commands, argv, env, tokens, l, exi);
	return (*status);
}