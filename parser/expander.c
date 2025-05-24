#include "../minishell.h"

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

char	*expand_word(const char *word, t_gc **gc, t_env *env)
{
    char    *res;
    char    *inner;
    char    *key;
    char    *val;
    int     i;
    int     j;

    res = ft_strdup_gc("", gc);
    val = NULL;
    i = 0;
    while (word[i])
    {
        if (word[i] == '\'')
        {
            j = i + 1;
            while (word[j] && word[j] != '\'')
                j++;
            res = ft_strjoin_gc(res, ft_strndup(word + i + 1, j - i - 1, gc), gc);
            i = j + 1;
        }
        else if (word[i] == '"')
        {
            j = i + 1;
            while (word[j] && word[j] != '"')
                j++;
            inner = ft_strndup(word + i + 1, j - i - 1, gc);
            res = ft_strjoin_gc(res, expand_word(inner, gc, env), gc);
            i = j + 1;
        }
        else if (word[i] == '$')
        {
            if (word[i + 1] == '?')
            {
                res = ft_strjoin_gc(res, ft_itoa_gc(g_exit_status, gc), gc);
                i += 2;
            }
            else
            {
                j = i + 1;
                while (ft_isalnum(word[j]) || word[j] == '_')
                    j++;
                key = ft_strndup(word + i + 1, j - i - 1, gc);
                val = get_env_val(key, env);
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
    return (res);
}
