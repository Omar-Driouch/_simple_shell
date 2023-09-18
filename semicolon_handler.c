#include "shell.h"

int semicolon_handler(char **cmd, char **ar, char **env, int *tok, int *l, int *ex, char *lin)
{
	int result = 0;
	char **cmdar = NULL;
	int i;

	(void)lin;

	free(lin);
	for (i = 0; cmd[i]; i++)
	{

		cmdar = (char **)malloc((2) * sizeof(char *));
		cmdar[0] = _strdup(cmd[i]);

		cmdar[1] = NULL;
		result = executecmd(cmdar, ar, env, tok, l, ex);
		*tok = *tok - 1;
	}
	free_2d_array(cmd);
	return result;
}

int chech_semicolon(char *source)
{
	int i;
	if (source == NULL)
	{
		return 0;
	}

	for (i = 0; source[i] != '\0'; i++)
	{
		if (source[i] == ';')
		{
			return 1;
		}
	}

	return 0;
}