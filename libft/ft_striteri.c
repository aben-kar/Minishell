/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:03:03 by acben-ka          #+#    #+#             */
/*   Updated: 2024/11/14 15:03:05 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	my_function(unsigned int i, char *str)
// {
// 	if (*str >= 'a' && *str <= 'z')
// 		*str -= 32;
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// int	main(void)
// {
// 	char *s;

// 	s = "hello";
// 	ft_striteri(s, my_function);
// 	printf("%s", s);
// 	return (0);
// }