#include "minishell.h"

void	garbageCollector(char** argv,int size)
{
    int i;

	i = 0;
	while (i < size)
		free(argv[i++]);
    free(argv);
    argv = NULL;
}