/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:48:31 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/24 20:48:32 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_invalid_token(t_token *tok)
{
	return (!tok || is_redir(tok->value) || ft_strcmp(tok->value, "|") == 0);
}

static bool	check_and_handle_pipe_start(t_token *tokens)
{
	if (tokens && ft_strcmp(tokens->value, "|") == 0)
	{
		bash_syntax_error("|");
		return (false);
	}
	return (true);
}

static bool	handle_token(t_command *cmd, t_token **tokens, t_gc **gc, t_env *env)
{
	int		type;
	char	*filename;
	char	*expanded;

	if (is_redir((*tokens)->value))
	{
		type = redir_type((*tokens)->value);
		*tokens = (*tokens)->next;
		if (is_invalid_token(*tokens))
		{
			bash_syntax_error(*tokens ? (*tokens)->value : NULL);
			return (false);
		}
		filename = expand_word((*tokens)->value, gc, env);
		cmd->redirects = add_redir(cmd->redirects, filename, type, gc);
		cmd->has_redirect = true;
	}
	else
	{
		expanded = expand_word((*tokens)->value, gc, env);
		if (!expanded)
			return (false);
		cmd->cmd = argv_add(cmd->cmd, expanded, gc);
	}
	return (true);
}

static t_command	*parse_single_command(t_token **tokens, t_gc **gc, t_env *env)
{
	t_command	*cmd;

	cmd = ft_calloc_gc(1, sizeof(t_command), gc);
	if (!cmd)
		return (NULL);
	while (*tokens && ft_strcmp((*tokens)->value, "|") != 0)
	{
		if (!handle_token(cmd, tokens, gc, env))
			return (NULL);
		*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_command	*parse_tokens(t_token *tokens, int *has_pipe, t_gc **gc, t_env *env)
{
	t_command	*cmds;
	t_command	*cmd;

	cmds = NULL;
	cmd = NULL;
	*has_pipe = 0;
	if (!tokens || !check_and_handle_pipe_start(tokens))
		return (NULL);
	while (tokens)
	{
		cmd = parse_single_command(&tokens, gc, env);
		if (!cmd)
			return (NULL);
		cmds = add_command(cmds, cmd);
		if (tokens && (!tokens->next || ft_strcmp(tokens->next->value, "|") == 0))
		{
			bash_syntax_error("|");
			return (NULL);
		}
		if (tokens)
		{
			*has_pipe = 1;
			tokens = tokens->next;
		}
	}
	return (cmds);
}
