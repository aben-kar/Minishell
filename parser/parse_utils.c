/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:28:26 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/30 17:28:27 by zaakrab          ###   ########.fr       */
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
	char	*file_name;

	if (type == REDIR_HEREDOC)
	{
		file_name = handle_heredoc(value, ctx->gc, ctx->env);
		if (NULL == file_name)
			return (NULL);
		return (file_name);
	}
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
	bool	was_quoted;

	if (!tokens || !*tokens || !(*tokens)->value)
	{
		bash_syntax_error("newline");
		g_exit_status = 1;
		return (false);
	}
	was_quoted = ((*tokens)->value[0] == '\'' || (*tokens)->value[0] == '"');
	if (is_token_invalid(tokens))
		return (false);
	filename = expand_filename(type, (*tokens)->value, ctx);
	if (!filename || !*filename)
		return (false);
	if (!was_quoted)
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
