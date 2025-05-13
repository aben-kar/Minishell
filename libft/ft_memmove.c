/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:19:47 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:19:49 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*tmpdst;
	unsigned char	*tmpsrc;
	size_t			i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (!len || dest == src)
		return ((void *)dest);
	tmpdst = (unsigned char *) dest;
	tmpsrc = (unsigned char *) src;
	if (tmpdst > tmpsrc)
		while (len-- > 0)
			tmpdst[len] = tmpsrc[len];
	else
	{
		while (i < len)
		{
			tmpdst[i] = tmpsrc[i];
			i++;
		}
	}
	return (dest);
}
