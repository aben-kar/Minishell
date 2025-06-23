/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:16:50 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/23 16:05:24 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_separator(char c, char *separators)
{
	int	i;

	i = 0;
	while (separators[i])
	{
		if (c == separators[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_word(char const *s1, char *sp)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 1;
	while (s1[i])
	{
		if (!is_separator(s1[i], sp) && check == 1)
		{
			count += 1;
			check = 0;
		}
		else if (is_separator(s1[i], sp))
			check = 1;
		i++;
	}
	return (count);
}

char	*ft_strsdup(char const *s, size_t *j, char *sp)
{
	char	*result;
	size_t	i;
	size_t	k;

	i = *j;
	while (!is_separator(s[*j], sp) && s[*j])
		(*j)++;
	result = (char *)malloc((*j - i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	k = 0;
	while (k < *j - i)
	{
		result[k] = s[i + k];
		k++;
	}
	result[k] = '\0';
	return (result);
}

void	ft_free(char **prr)
{
	int	i;

	i = 0;
	while (prr && prr[i])
	{
		free(prr[i]);
		i++;
	}
	if (prr)
		free(prr);
}

char	**ft_split(char const *s, char *c)
{
	t_split	var;

	var.i = 0;
	var.j = -1;
	var.len_word = count_word(s, c);
	if (!s || !var.len_word)
		return (NULL);
	var.prr = (char **)ft_calloc((var.len_word + 1), sizeof(char *));
	if (var.prr == NULL)
		return (NULL);
	while (++var.j < var.len_word)
	{
		while (is_separator(s[var.i], c) && s[var.i])
			var.i++;
		if (s[var.i])
		{
			var.prr[var.j] = ft_strsdup(s, &var.i, c);
			if (!var.prr[var.j])
			{
				ft_free(var.prr);
				return (NULL);
			}
		}
	}
	return (var.prr);
}
