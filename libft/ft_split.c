/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:16:50 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/13 16:29:53 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	ifchar(char c, char charset)
// {
// 	if (c == charset)
// 		return (1);
// 	return (0);
// }

// static int	count_words(const char *string, char charset)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = 0;
// 	while (string[i] != 0)
// 	{
// 		while (string[i] && ifchar(string[i], charset))
// 			i++;
// 		if (string[i] && !ifchar(string[i], charset))
// 			count++;
// 		while (string[i] && !ifchar(string[i], charset))
// 			i++;
// 	}
// 	return (count);
// }

// static char	*substring(const char *str, int first, int last)
// {
// 	int		i;
// 	char	*sub;

// 	sub = (char *)malloc(sizeof(char) * (last - first + 1));
// 	if (sub == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (first < last)
// 		sub[i++] = str[first++];
// 	sub[i] = 0;
// 	return (sub);
// }

// static void	free_strings(char **strs, int k)
// {
// 	int	i;

// 	i = 0;
// 	while (i < k)
// 		free (strs[i++]);
// 	free(strs);
// }

// char	**ft_split(const char *s, char c)
// {
// 	int		i[3];
// 	char	**strs;

// 	if (!s)
// 		return (NULL);
// 	strs = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
// 	if (strs == NULL)
// 		return (NULL);
// 	i[0] = 0;
// 	i[2] = 0;
// 	while (i[2] < count_words(s, c))
// 	{
// 		while (s[i[0]] && ifchar(s[i[0]], c))
// 			i[0]++;
// 		i[1] = i[0];
// 		while (s[i[1]] && !ifchar(s[i[1]], c))
// 			i[1]++;
// 		strs[i[2]] = substring(s, i[0], i[1]);
// 		if (strs[i[2]] == NULL)
// 			return (free_strings(strs, i[2]), NULL);
// 		i[2]++;
// 		i[0] = i[1];
// 	}
// 	strs[i[2]] = NULL;
// 	return (strs);
// }

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
	size_t	j;
	size_t	i;
	char	**prr;
	size_t	len_word;

	i = 0;
	j = 0;
	len_word = count_word(s, c);
	if (!s || !len_word)
		return (NULL);
	prr = (char **)ft_calloc((len_word + 1), sizeof(char *));
	if (prr == NULL)
		return (NULL);
	while (j < len_word)
	{
		while (is_separator(s[i], c) && s[i])
			i++;
		if (s[i])
		{
			prr[j] = ft_strsdup(s, &i, c);
			if (!prr[j])
			{
				ft_free(prr);
				return(NULL);
			}
			j++;
		}
	}
	return (prr);
}