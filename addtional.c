#include "shel.h"

void path(void)
{
	char *buf;
	size_t size;

	size = pathconf(".", _PC_PATH_MAX);
	buf = (char *)malloc((size_t)size);
	if (buf != NULL)
	{
		if (getcwd(buf, (size_t)size) != NULL)
		{
			_print_str(buf);
			_print_str("\n");
		}
		else
		{
			perror("getcwd");
		}
		free(buf);
	}
	else
	{
		perror("malloc");
	}
}

int changeDirectory(char *path)
{
	if (path == NULL)
	{
		_print_str("chdir: missing path\n");
		return (0);
	}

	if (chdir(path) == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
	free(path);
}




void free_2d_array(char **array)
{
	int i;

	if (array == NULL)
	{
		return;
	}

	for (i = 0; array[i]; i++)
	{
		if (array[i] != NULL)
		{
			free(array[i]);
		}
	}

	free(array);
}
