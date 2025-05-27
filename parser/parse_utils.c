/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:02:24 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/26 18:02:25 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_redirection(t_command *cmd, t_token **tokens,
	t_gc **gc, t_env *env, int type)
{
	char	*filename;

	if (type == REDIR_HEREDOC)
		filename = handle_heredoc((*tokens)->value, gc, env);
	else
		filename = expand_word((*tokens)->value, gc, env);
	if (!filename)
		return (false);
	cmd->redirects = add_redir(cmd->redirects, filename, type, gc);
	cmd->has_redirect = true;
	return (true);
}

bool	handle_argument(t_command *cmd, t_token *token,
	t_gc **gc, t_env *env)
{
	char	*expanded;

	expanded = expand_word(token->value, gc, env);
	if (!expanded)
		return (false);
	cmd->cmd = argv_add(cmd->cmd, expanded, gc);
	return (true);
}

char	*expand_inside_double_quotes(const char *str, t_gc **gc, t_env *env)
{
	char	*res = ft_strdup_gc("", gc);
	int		i = 0;

	while (str[i])
	{
		if (str[i] == '$')
			i = handle_dollar(str, &res, i, gc, env);
		else
		{
			res = ft_strjoin_char_gc(res, str[i], gc);
			i++;
		}
	}
	return (res);
}

int	handle_dollar(const char *word, char **res,
	int i, t_gc **gc, t_env *env)
{
	char	*key;
	char	*val;
	int		j;
	char	*exit_str;

	if (word[i + 1] == '?')
	{
		exit_str = ft_itoa_gc(g_exit_status, gc);
		*res = ft_strjoin_gc(*res, exit_str, gc);
		return (i + 2);
	}
	if (!word[i + 1] || (!ft_isalpha(word[i + 1]) && word[i + 1] != '_'))
	{
		// Treat invalid variable like "$" or "$)" as literal "$"
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
	return (j);
}