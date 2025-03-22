/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:08:39 by acben-ka          #+#    #+#             */
/*   Updated: 2024/11/13 18:08:40 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*dest;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (i == (int)ft_strlen(s1))
	{
		dest = ft_calloc(1, sizeof(char));
		if (!dest)
			return (NULL);
		return (dest);
	}
	j = ft_strlen(s1) - 1;
	while (j >= 0 && ft_strchr(set, s1[j]))
		j--;
	dest = ft_calloc((j - i + 2), sizeof(char));
	if (!dest)
		return (NULL);
	return (ft_memcpy(dest, s1 + i, j - i + 1));
}

// int	main(void)
// {
// 	// char s1[100] = "aaaaaa";
// 	// char set[100] = "!eh";
// 	char *str = ft_strtrim("", "");
// 	printf("%s\n", str);
// }