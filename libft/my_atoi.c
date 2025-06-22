/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:31:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/22 15:48:24 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_aatoi(char *s)
{
	t_atoi	vr;

	vr.i = 0;
	vr.rs = 0;
	vr.sign = 1;
	while ((s[vr.i] >= '\t' && s[vr.i] <= '\r') || s[vr.i] == ' ')
		vr.i++;
	if (s[vr.i] == '-' || s[vr.i] == '+')
	{
		if (s[vr.i] == '-')
			vr.sign = -1;
		vr.i++;
	}
	while (s[vr.i] >= '0' && s[vr.i] <= '9')
	{
		vr.digit = s[vr.i] - '0';
		if (((vr.rs * vr.sign) > (LLONG_MAX - vr.digit) / 10))
			return (LLONG_MAX);
		if (((vr.rs * vr.sign) < (LLONG_MIN + vr.digit) / 10))
			return (LLONG_MIN);
		vr.rs = vr.rs * 10 + vr.digit;
		vr.i++;
	}
	return (vr.rs * vr.sign);
}
