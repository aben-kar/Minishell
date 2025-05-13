/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:13:44 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:13:45 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t size)
{
	void	*arr;

	if (size != 0 && nelem > SIZE_MAX / size)
		return (NULL);
	arr = (void *)malloc(nelem * size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, (nelem * size));
	return (arr);
}
