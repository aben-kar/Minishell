/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:48:03 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/22 16:51:04 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*handle_operator_token(const char *input,
	int *i, t_token_helper *ctx)
{
	int		start;
	char	*val;

	start = *i;
	if ((input[*i] == '>' || input[*i] == '<') && input[*i] == input[*i + 1])
		*i += 2;
	else
		(*i)++;
	val = ft_substr_gc(input, start, *i - start, ctx->gc);
	ctx->last = add_token(ctx->last, val, ctx->gc);
	if (!ctx->head)
		ctx->head = ctx->last;
	return (ctx->last);
}

static bool	is_quote_error(const char *input, int i)
{
	return ((input[i] == '\'' || input[i] == '"')
		&& (input[i + 1] == '"' || input[i + 1] == '\''));
}

static bool	scan_word_loop(const char *input, int *i)
{
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (is_quote_error(input, *i))
			{
				ft_putstr_fd("Command '' not found\n", 2);
				return (false);
			}
			if (!skip_quoted(input, i))
				return (false);
		}
		else
			(*i)++;
	}
	return (true);
}

static t_token	*handle_word_token(const char *input,
	int *i, t_token_helper *ctx)
{
	int		start;
	char	*val;

	start = *i;
	if (!scan_word_loop(input, i))
		return (NULL);
	val = ft_substr_gc(input, start, *i - start, ctx->gc);
	ctx->last = add_token(ctx->last, val, ctx->gc);
	if (!ctx->head)
		ctx->head = ctx->last;
	return (ctx->last);
}

t_token	*tokenize(const char *input, t_gc **gc)
{
	int				i;
	t_token_helper	ctx;

	i = 0;
	ctx.head = NULL;
	ctx.last = NULL;
	ctx.gc = gc;
	while (input[i])
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			ctx.last = handle_operator_token(input, &i, &ctx);
		else
			ctx.last = handle_word_token(input, &i, &ctx);
		if (!ctx.last)
			return (NULL);
	}
	return (ctx.head);
}
