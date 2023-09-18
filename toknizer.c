#include "shell.h"

int tokenizer(char **line, int *tokens, char **commands,
			  char **argv, char **env, int *l, int *exi, int *status)
{
	char *token = NULL, *temp = NULL, *lin = _strdup(*line);
	int cpt = 0, i = 0, chek = chech_semicolon(*line);

	if (!*line || !*line[0] || _strcmp(*line, "\n") == 0)
	{
		*tokens = 0;
		return (0);
	}
	temp = _strdup(*line);
	token = strtok(temp, " \t\n\r\a;");
	while (token)
	{
		if (_strcmp(token, "#") == 0 && cpt != 0)
			break;
		cpt++;
		token = strtok(NULL, " \t\n\r\a;");
	}
	*tokens = cpt;
	commands = (char **)malloc(sizeof(char *) * (cpt + 1));
	token = strtok(*line, " \t\n\r\a;");
	while (token)
	{
		if (_strcmp(token, "#") == 0 && i != 0)
			break;
		commands[i] = _strdup(token);
		token = strtok(NULL, " \t\n\r\a;");
		i++;
	}
	free(temp), free(*line);
	*line = NULL;
	commands[i] = NULL;
	if (!chek)
	{
		free(lin);
		*status = executecmd(commands, argv, env, tokens, l, exi);
	}
	else
		*status = semicolon_handler(commands, argv, env, tokens, l, exi, lin);
	return (*status);
}
