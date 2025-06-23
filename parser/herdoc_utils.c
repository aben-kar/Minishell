/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 08:31:39 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/31 08:31:40 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_quoted_delimiter(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (true);
		str++;
	}
	return (false);
}

char	*remove_all_quotes(const char *input, t_gc **gc)
{
	int		i;
	int		j;
	char	*res;
	char	quote;

	i = 0;
	j = 0;
	res = gc_alloc(ft_strlen(input) + 1, gc);
	if (!res)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				res[j++] = input[i++];
			if (input[i] == quote)
				i++;
		}
		else
			res[j++] = input[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*get_delimiter(const char *raw_delim, t_gc **gc)
{
	t_token	*token;
	char	*delimiter;

	if (ft_strcmp(raw_delim, "\"\"") == 0)
		return ("");
	token = tokenize(raw_delim, gc);
	if (!token || token->next)
		return (NULL);
	delimiter = token->value;
	return (remove_all_quotes(delimiter, gc));
}

char	*generate_temp_filename(t_gc **gc)
{
	static int	counter;
	char		*num;
	char		*filename;

	num = NULL;
	filename = NULL;
	counter = counter + 1;
	num = ft_itoa_gc(counter, gc);
	filename = ft_strjoin_gc("/tmp/.heredoc", num, gc);
	return (filename);
}
