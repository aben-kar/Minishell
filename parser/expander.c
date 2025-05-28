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

char    *get_env_val(const char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int handle_dollar(const char *word, char **res, int i, t_gc **gc, t_env *env)
{
	char    *key;
	char    *val;
	int     j;
	char    *exit_str;

	if (word[i + 1] == '?')
	{
		exit_str = ft_itoa_gc(g_exit_status, gc);
		*res = ft_strjoin_gc(*res, exit_str, gc);
		return (i + 2);
	}
	if (!word[i + 1] || (!ft_isalpha(word[i + 1]) && word[i + 1] != '_'))
	{
		*res = ft_strjoin_char_gc(*res, '$', gc);
		return (i + 1);
	}
	j = i + 1;
	while (ft_isalnum(word[j]) || word[j] == '_')
		j++;
	key = ft_strndup(word + i + 1, j - i - 1, gc);
	val = get_env_val(key, env);
	if (val)
		*res = ft_strjoin_gc(*res, ft_strdup_gc(val, gc), gc);
	// else
	//     *res = ft_strjoin_gc(*res, ft_strdup_gc("", gc), gc); COMMENTED NOW
	return (j);
}

char    *expand_word_always_expand(const char *word, t_gc **gc, t_env *env)
{
	char	*res;
	int		i;

	res = ft_strdup_gc("", gc);
	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
			i = handle_dollar(word, &res, i, gc, env);
		else
		{
			res = ft_strjoin_char_gc(res, word[i], gc);
			i++;
		}
	}
	return (res);
}

char	*expand_word(const char *word, t_gc **gc, t_env *env)
{
	char	*res;
	int		i;
	bool	in_single;
	bool	in_double;

	res = ft_strdup_gc("", gc);
	i = 0;
	in_single = false;
	in_double = false;
	while (word[i])
	{
		if (word[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
		}
		else if (word[i] == '"' && !in_single)
		{
			in_double = !in_double;
			i++;
		}
		else if (word[i] == '$' && !in_single)
			i = handle_dollar(word, &res, i, gc, env);
		else
		{
			res = ft_strjoin_char_gc(res, word[i], gc);
			i++;
		}
	}
	return (res);
}

// void	expand_command(t_command *cmd, t_env *env, t_gc **gc)
// {
// 	int		i;
// 	int		j;
// 	char	*expanded;

// 	if (!cmd || !cmd->cmd)
// 		return ;
// 	i = 0;
// 	while (cmd->cmd[i])
// 	{
// 		expanded = expand_word(cmd->cmd[i], gc, env);
// 		cmd->cmd[i] = expanded;
// 		i++;
// 	}
// 	i = 0;
// 	j = 0;
// 	while (cmd->cmd[i])
// 	{
// 		if (i == 0 || cmd->cmd[i][0] != '\0')
// 		{
// 			cmd->cmd[j] = cmd->cmd[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	cmd->cmd[j] = NULL;
// }
