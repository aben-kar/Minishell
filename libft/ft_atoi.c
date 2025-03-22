/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:19:52 by acben-ka          #+#    #+#             */
/*   Updated: 2024/11/16 15:57:48 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	rs;
	int	sign;

	i = 0;
	rs = 0;
	sign = 1;
	while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		rs = rs * 10 + (s[i] - 48);
		if (rs * sign > INT_MAX)
			return (INT_MAX);
		if (rs * sign < INT_MIN)
			return (INT_MIN);
		i++;
	}
	return (rs * sign);
}
