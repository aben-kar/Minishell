/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:22:30 by acben-ka          #+#    #+#             */
/*   Updated: 2024/11/12 20:06:14 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_sr;
	size_t	len_ds;
	size_t	i;

	len_sr = ft_strlen(src);
	if (size == 0)
		return (len_sr);
	len_ds = ft_strlen(dest);
	if (size < len_ds)
		return (size + len_sr);
	i = 0;
	while (src[i] && len_ds + i < size - 1)
	{
		dest[len_ds + i] = src[i];
		i++;
	}
	dest[len_ds + i] = '\0';
	return (len_ds + len_sr);
}
// int main() {
//     char dest[30] = "hello";
//     char src[30] = "World!";
//     size_t result = ft_strlcat(dest, src, 6);
//     printf("%zu\n", result);
//     char dest2[30] = "hello";
//     char src1[30] = "World!";
//     size_t result2 = strlcat(dest2, src1, 6);
//     printf("%zu\n", result2);
// }