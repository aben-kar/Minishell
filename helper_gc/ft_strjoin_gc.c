/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:17:17 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:17:18 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_gc(const char *s1, const char *s2, t_gc **gc)
{
	char	*result;
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = gc_alloc(sizeof(char) * (s1_len + s2_len + 1), gc);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		result[i] = s1[i];
	j = 0;
	while (j < s2_len)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

char	*my_strjoin(char *s1, char *s2, t_gc **gc)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = gc_alloc(s1_len + s2_len + 1, gc);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, s1_len);
	ft_memcpy(result + s1_len, s2, s2_len);
	result[s1_len + s2_len] = '\0';
	return (result);
}
