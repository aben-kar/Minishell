/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:17:42 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:17:43 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;
	size_t	total_length;

	i = 0;
	len_dst = ft_strlen(dst);
	j = len_dst;
	total_length = len_dst + ft_strlen(src);
	if (!dst && size == 0)
		return (ft_strlen(src));
	if (j >= size)
		return (total_length - (j - size));
	while (src[i] != '\0' && (i + len_dst) < size - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (total_length);
}
