/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:16:03 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:16:04 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*tmpdst;
	const unsigned char	*tmpsrc;
	size_t				i;

	tmpdst = (unsigned char *) dest;
	tmpsrc = (const unsigned char *) src;
	if (tmpdst == NULL && tmpsrc == NULL)
		return (NULL);
	if (dest == src)
		return (dest);
	i = 0;
	while (i < n)
	{
		tmpdst[i] = tmpsrc[i];
		i++;
	}
	return (dest);
}
