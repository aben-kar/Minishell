/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:48:15 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/25 16:28:31 by zaakrab          ###   ########.fr       */
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

static int	handle_double_quote(const char *word, char **res,
	int i, t_gc **gc, t_env *env)
{
	int		j;
	char	*inner;

	j = i + 1;
	while (word[j] && word[j] != '"')
		j++;
	inner = ft_strndup(word + i + 1, j - i - 1, gc);
	*res = ft_strjoin_gc(*res, expand_inside_double_quotes(inner, gc, env), gc);
	return (j + 1);
}

// static int	handle_dollar(const char *word, char **res,
// 	int i, t_gc **gc, t_env *env)
// {
// 	char	*key;
// 	char	*val;
// 	int		j;
// 	char	*exit_str;

// 	if (word[i + 1] == '?')
// 	{
// 		exit_str = ft_itoa_gc(g_exit_status, gc);
// 		*res = ft_strjoin_gc(*res, exit_str, gc);
// 		return (i + 2);
// 	}
// 	if (!word[i + 1] || (!ft_isalpha(word[i + 1]) && word[i + 1] != '_'))
// 	{
// 		// Treat invalid variable like "$" or "$)" as literal "$"
// 		*res = ft_strjoin_char_gc(*res, '$', gc);
// 		return (i + 1);
// 	}
// 	j = i + 1;
// 	while (ft_isalnum(word[j]) || word[j] == '_')
// 		j++;
// 	key = ft_strndup(word + i + 1, j - i - 1, gc);
// 	val = get_env_val(key, env);
// 	if (val)
// 		*res = ft_strjoin_gc(*res, ft_strdup_gc(val, gc), gc);
// 	return (j);
// }

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
