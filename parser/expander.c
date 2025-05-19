// #include "minishell.h"
#include "../minishell.h"

// yes yes yes you know what time it is bruv
char	*get_env_val(const char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
// this function is used to expand the variable

// char	*expand_var(char *word, t_gc **gc, t_env *env)
// {
// 	char	*inner;
// 	char	*val;
// 	int		len;

// 	if (!word)
// 		return (NULL);
// 	if (word[0] == '$' && word[1] == '?')
// 		return (ft_itoa_gc(g_exit_status, gc));
// 	len = ft_strlen(word);
// 	if (word[0] == '\'' && word[len - 1] == '\'')
// 	{
// 		// single quotes: no expansion, strip quotes
// 		return (ft_strndup((word + 1), (len - 2), gc));
// 	}
// 	else if (word[0] == '"' && word[len - 1] == '"')
// 	{
// 		// double quotes: strip quotes and expand if starts with $
// 		inner = ft_strndup((word + 1), (len - 2), gc);
// 		if (inner && ft_strncmp(inner, "$?", 2) == 0 && inner[2] == '\0')
// 		{
// 			// free(inner);
// 			return (ft_itoa_gc(g_exit_status, gc));
// 		}
// 		if (inner && inner[0] == '$')
// 		{
// 			val = get_env_val(inner + 1, env);
// 			// free(inner);
// 			if (val)
// 				return (ft_strdup_gc(val, gc));
// 			else
// 				return (ft_strdup_gc("", gc));
// 		}
// 		// no variable to expand, return as is
// 		return (inner);
// 	}
// 	else if (word[0] == '$')
// 	{
// 		// unquoted variable
// 		val = get_env_val(word + 1, env);
// 		if (val)
// 			return (ft_strdup_gc(val, gc));
// 		else
// 			return (ft_strdup_gc("", gc));
// 	}
// 	// not a variable, return a copy of the word
// 	return (ft_strdup_gc(word, gc));
// }

char	*expand_word(const char *word, t_gc **gc, t_env *env)
{
    char *res = ft_strdup_gc("", gc);
    int i = 0;

    while (word[i])
    {
        if (word[i] == '\'') // single quotes: copy until next '
        {
            int j = i + 1;
            while (word[j] && word[j] != '\'')
                j++;
            res = ft_strjoin_gc(res, ft_strndup(word + i + 1, j - i - 1, gc), gc);
            i = j + 1;
        }
        else if (word[i] == '"') // double quotes: process inside
        {
            int j = i + 1;
            while (word[j] && word[j] != '"')
                j++;
            char *inner = ft_strndup(word + i + 1, j - i - 1, gc);
            res = ft_strjoin_gc(res, expand_word(inner, gc, env), gc);
            i = j + 1;
        }
        else if (word[i] == '$') // variable expansion
        {
            if (word[i + 1] == '?')
            {
                res = ft_strjoin_gc(res, ft_itoa_gc(g_exit_status, gc), gc);
                i += 2;
            }
            else
            {
                int j = i + 1;
                while (ft_isalnum(word[j]) || word[j] == '_')
                    j++;
                char *key = ft_strndup(word + i + 1, j - i - 1, gc);
                char *val = get_env_val(key, env);
                res = ft_strjoin_gc(res, ft_strdup_gc(val ? val : "", gc), gc);
                i = j;
            }
        }
        else
        {
            res = ft_strjoin_char_gc(res, word[i], gc);
            i++;
        }
    }
    return res;
}
