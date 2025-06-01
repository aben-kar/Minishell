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

bool	is_quoted_delimiter(const char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	if (len >= 2 && ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
			|| (delimiter[0] == '"' && delimiter[len - 1] == '"')))
		return (true);
	return (false);
}

char	*strip_quotes(const char *str, t_gc **gc)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '"' && str[len - 1] == '"')))
		return (ft_strndup(str + 1, len - 2, gc));
	return (ft_strdup_gc(str, gc));
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
