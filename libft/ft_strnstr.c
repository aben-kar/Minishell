/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:18:46 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:18:47 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big && !len)
		return (0);
	if (!big && len == 0)
		return (NULL);
	if (!little || little == big)
		return ((char *)big);
	i = 0;
	while (big[i] != 0)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (big[i + j] == 0 && little[j] == 0)
				return ((char *) &big[i]);
			j++;
		}
		if (little[j] == 0)
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
