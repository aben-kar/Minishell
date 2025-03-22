/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:02:17 by acben-ka          #+#    #+#             */
/*   Updated: 2024/11/14 15:02:18 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (num != 0 && (18446744073709551615UL / num < size))
		return (NULL);
	total_size = num * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}

// int main() {
//     size_t num = 0;
//     size_t size = sizeof(int);
//    // size_t i = 0;

//     char *array = calloc(num, size);

//    // while (i < num)
//     //{
//         printf("%d\n", *array);
//         //i++;
//     //}
//     free(array);
//     return (0);
// }