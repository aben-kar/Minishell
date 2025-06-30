/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:48:15 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/02 22:18:49 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_quote_state(char c, bool *in_single, bool *in_double)
{
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	if (c == '"' && !*in_single)
		*in_double = !*in_double;
}

static void	init_expand_ctx(t_expand_helper *ctx, t_gc **gc,
	t_env *env, char **res)
{
	*res = ft_strdup_gc("", gc);
	ctx->gc = gc;
	ctx->env = env;
	ctx->res = res;
}

static int	handle_expansion(const char *word, int i, t_expand_helper *ctx,
	bool *in_single)
{
	if (word[i + 1] == '"' || word[i + 1] == '\'' || word[i + 1] == '\0')
	{
		handle_simple_dollar(ctx);
		return (i + 1);
	}
	if (word[i + 1] == '$')
	{
		handle_simple_dollar(ctx);
		return (i + 1);
	}
	if (!*in_single)
		return (handle_dollar(word, i, ctx));
	return (handle_char(word, i, ctx));
}

char	*expand_word(const char *word, t_gc **gc, t_env *env)
{
	int				i;
	bool			in_single;
	bool			in_double;
	t_expand_helper	ctx;
	char			*res;

	i = 0;
	in_single = false;
	in_double = false;
	init_expand_ctx(&ctx, gc, env, &res);
	while (word[i])
	{
		update_quote_state(word[i], &in_single, &in_double);
		if ((word[i] == '\'' && !in_double) || (word[i] == '"' && !in_single))
			i++;
		else if (word[i] == '$' && !in_single)
			i += handle_expansion(word, i, &ctx, &in_single);
		else
			i = handle_char(word, i, &ctx);
	}
	return (res);
}
