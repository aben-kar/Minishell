/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:22:45 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/02 22:18:14 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_word_always_expand(const char *word, t_gc **gc, t_env *env)
{
	int				i;
	bool			in_single;
	t_expand_helper	ctx;
	char			*res;

	i = 0;
	in_single = false;
	init_expand_ctx(&ctx, gc, env, &res);
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
		{
			*(ctx.res) = ft_strjoin_char_gc(*(ctx.res), word[i], ctx.gc);
			i++;
		}
		else if (word[i] == '$')
			i += handle_expansion(word, i, &ctx, &in_single);
		else
			i = handle_char(word, i, &ctx);
	}
	return (res);
}

int	handle_exit_code(t_expand_helper *ctx)
{
	char	*exit_str;

	exit_str = ft_itoa_gc(g_exit_status, ctx->gc);
	*(ctx->res) = ft_strjoin_gc(*(ctx->res), exit_str, ctx->gc);
	return (2);
}

int	handle_simple_dollar(t_expand_helper *ctx)
{
	*(ctx->res) = ft_strjoin_char_gc(*(ctx->res), '$', ctx->gc);
	return (1);
}

int	get_key_end_index(const char *word, int i)
{
	int	j;

	j = i + 1;
	if (ft_isdigit(word[j]))
		return (j + 1);
	while (ft_isalnum(word[j]) || word[j] == '_')
		j++;
	return (j);
}

int	handle_dollar_inner(const char *word, int i, t_expand_helper *ctx)
{
	char	*key;
	char	*val;
	int		j;

	j = get_key_end_index(word, i);
	key = ft_strndup(word + i + 1, j - i - 1, ctx->gc);
	val = get_env_val(key, ctx->env);
	if (val)
		*(ctx->res) = ft_strjoin_gc(*(ctx->res),
				ft_strdup_gc(val, ctx->gc), ctx->gc);
	return (j - i);
}
