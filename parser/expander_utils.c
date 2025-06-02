/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:22:38 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/02 22:17:35 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_val(const char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	handle_dollar(const char *word, int i, t_expand_helper *ctx)
{
	if (word[i + 1] == '?')
		return (handle_exit_code(ctx));
	if (!word[i + 1])
		return (handle_simple_dollar(ctx));
	if (!ft_isalpha(word[i + 1]) && word[i + 1] != '_')
		return (handle_simple_dollar(ctx));
	return (handle_dollar_inner(word, i, ctx));
}

int	handle_char(const char *word, int i, t_expand_helper *ctx)
{
	*(ctx->res) = ft_strjoin_char_gc(*(ctx->res), word[i], ctx->gc);
	return (i + 1);
}

bool	skip_quoted(const char *input, int *i) // tokenizer helper
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
	{
		(*i)++;
		return (true);
	}
	bash_unclosed_quote_error(quote);
	return (false);
}
