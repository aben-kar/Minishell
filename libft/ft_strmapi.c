/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:18:32 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:18:33 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*mapped;
	unsigned int	i;
	unsigned int	len;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	mapped = (char *)malloc(sizeof(char) * (len + 1));
	if (!mapped)
		return (NULL);
	while (i < len)
	{
		mapped[i] = (*f)(i, s[i]);
		i++;
	}
	mapped[i] = 0;
	return (mapped);
}
