/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:48:15 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/24 20:48:16 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	handle_single_quote(const char *word, char **res, int i, t_gc **gc)
{
	int	j;

    j = i + 1;
	while (word[j] && word[j] != '\'')
		j++;
	*res = ft_strjoin_gc(*res, ft_strndup(word + i + 1, j - i - 1, gc), gc);
	return (j + 1);
}

static int	handle_double_quote(const char *word, char **res, int i, t_gc **gc, t_env *env)
{
	int		j;
	char	*inner;

    j = i + 1;
	while (word[j] && word[j] != '"')
		j++;
	inner = ft_strndup(word + i + 1, j - i - 1, gc);
	*res = ft_strjoin_gc(*res, expand_word(inner, gc, env), gc);
	return (j + 1);
}

static int	handle_dollar(const char *word, char **res, int i, t_gc **gc, t_env *env)
{
	char	*key;
	char	*val;
	int		j;

	if (word[i + 1] == '?')
	{
		*res = ft_strjoin_gc(*res, ft_itoa_gc(g_exit_status, gc), gc);
		return (i + 2);
	}
	j = i + 1;
	while (ft_isalnum(word[j]) || word[j] == '_')
		j++;
	key = ft_strndup(word + i + 1, j - i - 1, gc);
	val = get_env_val(key, env);
	*res = ft_strjoin_gc(*res, ft_strdup_gc(val ? val : "", gc), gc);
	return (j);
}

char	*expand_word(const char *word, t_gc **gc, t_env *env)
{
	char	*res;
	int		i;

	res = ft_strdup_gc("", gc);
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			i = handle_single_quote(word, &res, i, gc);
		else if (word[i] == '"')
			i = handle_double_quote(word, &res, i, gc, env);
		else if (word[i] == '$')
			i = handle_dollar(word, &res, i, gc, env);
		else
		{
			res = ft_strjoin_char_gc(res, word[i], gc);
			i++;
		}
	}
	return (res);
}
