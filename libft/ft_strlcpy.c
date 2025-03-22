/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:22:34 by acben-ka          #+#    #+#             */
/*   Updated: 2024/11/12 20:11:47 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len);
}
// int main()
// {
//     //char src[] = "pooooool";
//     char destt[10];
//     printf ("%zu\n", ft_strlcpy(destt, NULL, 0));
//     printf ("%s\n", destt);

//     // //char src1[] = "pooooool";
//     // char dest[10];

//     // printf ("%zu\n", strlcpy(dest, NULL, 0));
//     // printf ("%s", dest);
// }