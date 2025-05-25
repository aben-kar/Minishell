/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aatoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:31:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/25 18:33:01 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_aatoi(char *s)
{
	int	i;
	long long	rs;
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
		int digit = s[i] - '0';

		if (((rs * sign) > (LLONG_MAX - digit) / 10))
			return (11);
		if (((rs * sign) < (LLONG_MIN + digit) / 10))
			return (11);
		rs = rs * 10 + digit;
		i++;
	}
	return (rs * sign);
}
