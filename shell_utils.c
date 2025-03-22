#include "shell.h"

char	**get_path(char **envp)
{
	char	*found;
	char	**split_path;

	while (*envp)
	{
		found = ft_strnstr(*envp, "PATH=", 5);
		if (found)
		{
			split_path = ft_split(found + 5, ':');
            // if (!split_path)
            // {
            //     ft_free(split_path);
            //     return(NULL);
            // }
			return (split_path);
		}
		envp++;
	}
	return (NULL);
}
