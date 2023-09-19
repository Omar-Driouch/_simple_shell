#include "shell.h"

/**
 * tokenizer - Tokenize and process input line into commands.
 * @line: A pointer to a pointer to the input line to be tokenized.
 * @tokens: A pointer to an integer to store the number of tokens.
 * @commands: A pointer to an array of strings to store the parsed commands.
 * @argv: A pointer to an array of strings representing program arguments.
 * @env: A pointer to an array of strings representing the environment.
 * @l: A pointer to an integer representing the line number.
 * @exi: A pointer to an integer representing the exit status.
 * @status: A pointer to an integer to store the final status.
 *
 * Return: The final status after command execution.
 */
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
	token = strtok(temp, DELIMITERS);
	while (token)
	{
		if ((_strcmp(token, "#") == 0 && i != 0) || _strcmp(token, "||") == 0)
			break;
		cpt++;
		token = strtok(NULL, DELIMITERS);
	}
	*tokens = cpt;
	commands = (char **)malloc(sizeof(char *) * (cpt + 1));
	token = strtok(*line, DELIMITERS);
	while (token)
	{
		if ((_strcmp(token, "#") == 0 && i != 0) || _strcmp(token, "||") == 0)
			break;
		commands[i] = _strdup(token);
		token = strtok(NULL, DELIMITERS);
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
