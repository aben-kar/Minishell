/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:19:07 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:19:08 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

char	*ft_substr_gc(const char *s, unsigned int start, size_t len, t_gc **gc)
{
	char	*subs;
	size_t	i;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup_gc("", gc));
	if (start + len > slen)
		len = slen - start;
	subs = gc_alloc(len + 1, gc);
	if (!subs)
		return (NULL);
	i = 0;
	while (s[start] != 0 && i < len)
		subs[i++] = s[start++];
	subs[i] = 0;
	return (subs);
}
