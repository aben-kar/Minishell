// #include "minishell.h"
#include "../minishell.h"

// yes yes yes you know what time it is bruv
char	*expand_var(char *word, t_gc **gc)
{
	char	*inner;
	char	*val;
	int		len;

	if (!word)
		return (NULL);
	if (word[0] == '$' && word[1] == '?')
		return (ft_itoa_gc(g_exit_status, gc));
	len = ft_strlen(word);
	if (word[0] == '\'' && word[len - 1] == '\'')
	{
		// single quotes: no expansion, strip quotes
		return (ft_strndup((word + 1), (len - 2), gc));
	}
	else if (word[0] == '"' && word[len - 1] == '"')
	{
		// double quotes: strip quotes and expand if starts with $
		inner = ft_strndup((word + 1), (len - 2), gc);
		if (inner && ft_strncmp(inner, "$?", 2) == 0 && inner[2] == '\0')
		{
			// free(inner);
			return (ft_itoa_gc(g_exit_status, gc));
		}
		if (inner && inner[0] == '$')
		{
			val = getenv(inner + 1);
			// free(inner);
			if (val)
				return (ft_strdup_gc(val, gc));
			else
				return (ft_strdup_gc("", gc));
		}
		// no variable to expand, return as is
		return (inner);
	}
	else if (word[0] == '$')
	{
		// unquoted variable
		val = getenv(word + 1);
		if (val)
			return (ft_strdup_gc(val, gc));
		else
			return (ft_strdup_gc("", gc));
	}
	// not a variable, return a copy of the word
	return (ft_strdup_gc(word, gc));
}
