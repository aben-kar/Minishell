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
		filename = handle_heredoc((*tokens)->value, gc);
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
