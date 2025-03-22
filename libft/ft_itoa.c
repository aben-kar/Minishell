/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:20:44 by acben-ka          #+#    #+#             */
/*   Updated: 2024/11/12 15:20:45 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nbr(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*convert_str(char *p, int nbr)
{
	int	len;

	len = count_nbr(nbr);
	if (nbr == -2147483648)
	{
		ft_strcpy(p, "-2147483648");
		return (p);
	}
	if (nbr == 0)
	{
		p[0] = '0';
		return (p);
	}
	if (nbr < 0)
	{
		p[0] = '-';
		nbr = -nbr;
	}
	while (nbr)
	{
		p[len - 1] = (nbr % 10) + 48;
		nbr /= 10;
		len--;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	int		len_nbr;
	char	*str;

	len_nbr = count_nbr(n);
	str = (char *)malloc((len_nbr + 1) * sizeof(char));
	if (!str)
		return (NULL);
	convert_str(str, n);
	str[len_nbr] = '\0';
	return (str);
}

// int	main(void)
// {
// 	char *sttr = ft_itoa(-2147483648);
// 	printf("%s", sttr);
// }