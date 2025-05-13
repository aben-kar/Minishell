/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:13:37 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:13:39 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	if (n == 0 || s == NULL)
		return ;
	tmp = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		tmp[i] = 0;
		i++;
	}
}
