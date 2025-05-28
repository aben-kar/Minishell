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

bool    handle_redirection(t_command *cmd, t_token **tokens,
    t_gc **gc, t_env *env, int type)
{
    char    *filename;
    char    *end;

    if (!tokens || !*tokens || !(*tokens)->value)
    {
        bash_syntax_error("newline");
        return (false);
    }
    filename = (*tokens)->value;
    if (type == REDIR_HEREDOC)
        filename = handle_heredoc(filename, gc, env);
    else
        filename = expand_word(filename, gc, env);
    if (!filename)
    {
        g_exit_status = 1;
        return (false);
    }
    while (*filename && ft_isspace(*filename))
        filename++;
    end = filename + ft_strlen(filename) - 1;
    while (end > filename && ft_isspace(*end))
        end--;
    *(end + 1) = '\0';
    if (!*filename)
    {
        bash_syntax_error("newline");
        return (false);
    }
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
