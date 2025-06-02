/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:48:31 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/25 16:35:49 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_invalid_token(t_token *tok)
{
	return (!tok || is_redir(tok->value) || ft_strcmp(tok->value, "|") == 0);
}

static bool	handle_token(t_command *cmd, t_token **tokens, t_expctx *ctx)
{
	int		type;
	char	*value;

	if (is_redir((*tokens)->value))
	{
		type = redir_type((*tokens)->value);
		*tokens = (*tokens)->next;
		if (is_invalid_token(*tokens))
		{
			if (*tokens)
				value = (*tokens)->value;
			else
				value = NULL;
			bash_syntax_error(value);
			return (false);
		}
		return (handle_redirection(cmd, tokens, ctx, type));
	}
	return (handle_argument(cmd, *tokens, ctx));
}

static t_command	*parse_single_command(t_token **tokens, t_expctx *ctx)
{
	t_command	*cmd;
	char		*expanded;

	cmd = ft_calloc_gc(1, sizeof(t_command), ctx->gc);
	if (!cmd)
		return (NULL);
	while (*tokens && ft_strcmp((*tokens)->value, "|") != 0)
	{
		if (!handle_token(cmd, tokens, ctx))
			return (NULL);
		*tokens = (*tokens)->next;
	}
	if (!cmd->cmd || !cmd->cmd[0])
		return (NULL);
	if (cmd->cmd && cmd->cmd[0] && cmd->cmd[0][0] == '$')
	{
		expanded = expand_word(cmd->cmd[0], ctx->gc, ctx->env);
		if (!expanded || expanded[0] == '\0')
			cmd->cmd[0] = "";
		else
			cmd->cmd[0] = expanded;
	}
	return (cmd);
}

static bool	validate_pipes(t_token *tokens, int *has_pipe)
{
	t_token	*tmp;

	tmp = tokens;
	*has_pipe = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "|") == 0)
		{
			*has_pipe = 1;
			if (tmp == tokens || !tmp->next)
			{
				bash_syntax_error("|");
				return (false);
			}
			if (ft_strcmp(tmp->next->value, "|") == 0)
			{
				bash_syntax_error("|");
				return (false);
			}
		}
		tmp = tmp->next;
	}
	return (true);
}

t_command	*parse_tokens(t_token *tokens, int *has_pipe, t_gc **gc, t_env *env)
{
	t_command	*cmds;
	t_command	*cmd;
	t_expctx	ctx;

	cmds = NULL;
	cmd = NULL;
	if (!tokens)
		return (NULL);
	if (!validate_pipes(tokens, has_pipe))
		return (NULL);
	ctx.gc = gc;
	ctx.env = env;
	while (tokens)
	{
		cmd = parse_single_command(&tokens, &ctx);
		if (!cmd)
			return (NULL);
		cmds = add_command(cmds, cmd);
		if (tokens && ft_strcmp(tokens->value, "|") == 0)
			tokens = tokens->next;
	}
	return (cmds);
}
