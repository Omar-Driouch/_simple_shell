#include "shel.h"

char *newpathh(void)
{
	char *buf = NULL;
	size_t size;

	size = pathconf(".", _PC_PATH_MAX);
	buf = (char *)malloc((size_t)size);
	if (buf != NULL)
	{
		if (getcwd(buf, (size_t)size) != NULL)
		{
			/* _print_str(buf);
			_print_str("\n"); */
		}
		else
		{
			perror("getcwd");
		}
		return (buf);
	}
	else
	{
		perror("malloc");
	}
	return (buf);
}

int changeDirectory(char *path)
{

	
	if (path == NULL)
	{
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
	/* free(path); */
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
