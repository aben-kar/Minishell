/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:02:24 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/02 22:20:05 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_argument(t_command *cmd, t_token *token, t_minus_param *ctx)
{
	char	*expanded;

	expanded = expand_word(token->value, ctx->gc, ctx->env);
	if (!expanded)
		return (false);
	cmd->cmd = argv_add(cmd->cmd, expanded, ctx->gc);
	return (true);
}

static bool	is_token_invalid(t_token **tokens)
{
	if (!tokens || !*tokens || !(*tokens)->value)
	{
		bash_syntax_error("newline");
		return (true);
	}
	return (false);
}

static char	*expand_filename(int type, char *value, t_minus_param *ctx)
{
	if (type == REDIR_HEREDOC)
		return (handle_heredoc(value, ctx->gc, ctx->env));
	return (expand_word(value, ctx->gc, ctx->env));
}

static void	trim_filename(char **filename)
{
	char	*start;
	char	*end;

	start = *filename;
	while (*start && ft_isspace(*start))
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	*(end + 1) = '\0';
	*filename = start;
}

bool	handle_redirection(t_command *cmd, t_token **tokens,
	t_minus_param *ctx, int type)
{
	char	*filename;

	if (is_token_invalid(tokens))
		return (false);
	filename = expand_filename(type, (*tokens)->value, ctx);
	if (!filename)
	{
		g_exit_status = 1;
		return (false);
	}
	trim_filename(&filename);
	if (!*filename)
	{
		bash_syntax_error("newline");
		return (false);
	}
	cmd->redirects = add_redir(cmd->redirects, filename, type, ctx->gc);
	cmd->has_redirect = true;
	return (true);
}
