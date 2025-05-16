/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:14:34 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:14:35 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

static	int	dig_count(int n)
{
	int	count;

	if (n == -2147483648)
		return (11);
	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 9)
	{
		count++;
		n = n / 10;
	}
	count++;
	return (count);
}

char	*ft_itoa_gc(int n, t_gc **gc)
{
	char			*str;
	int				i;
	int				len;
	unsigned int	nb;

	len = dig_count(n);
	str = gc_alloc((len + 1), gc);
	if (!str)
		return (NULL);
	if (n > 0)
		nb = n;
	else
		nb = -n;
	i = len - 1;
	while (i >= 0)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
		i--;
		if (n < 0)
			str[0] = '-';
	}
	str[len] = 0;
	return (str);
}
