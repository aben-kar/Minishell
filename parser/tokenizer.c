/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:48:03 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/24 20:48:04 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_whitespace(const char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
}

static t_token	*handle_operator_token(const char *input, int *i,
	t_token *last, t_token **head, t_gc **gc)
{
	int		start;
	char	*val;

	start = *i;
	if ((input[*i] == '>' || input[*i] == '<') && input[*i] == input[*i + 1])
		*i += 2;
	else
		(*i)++;
	val = ft_substr_gc(input, start, *i - start, gc);
	last = add_token(last, val, gc);
	if (!*head)
		*head = last;
	return (last);
}

bool	skip_quoted(const char *input, int *i)
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

static t_token *handle_word_token(const char *input, int *i,
	t_token *last, t_token **head, t_gc **gc)
{
	int     start;
	char    *val;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!skip_quoted(input, i))
				return (NULL);
		}
		else
			(*i)++;
	}
	val = ft_substr_gc(input, start, *i - start, gc);
	last = add_token(last, val, gc);
	if (!*head)
		*head = last;
	return (last);
}

t_token *tokenize(const char *input, t_gc **gc)
{
	int     i;
	t_token *head;
	t_token *last;

	i = 0;
	head = NULL;
	last = NULL;
	while (input[i])
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break;
			
		if (is_operator(input[i]))
			last = handle_operator_token(input, &i, last, &head, gc);
		else
			last = handle_word_token(input, &i, last, &head, gc);
			
		if (!last)
			return (NULL);
	}
	return (head);
}
