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
	t_expand_helper	ctx;
	char			*result;

	i = 0;
	result = ft_strdup_gc("", gc);
	ctx.gc = gc;
	ctx.env = env;
	ctx.res = &result;
	while (word[i])
	{
		if (word[i] == '$')
			i = handle_dollar(word, i, &ctx);
		else
			i = handle_char(word, i, &ctx);
	}
	return (result);
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
