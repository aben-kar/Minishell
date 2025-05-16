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

// #include "minishell.h"
#include "../minishell.h"

void	*ft_calloc_gc(size_t nelem, size_t size, t_gc **gc)
{
	void	*arr;

	if (size != 0 && nelem > SIZE_MAX / size)
		return (NULL);
	arr = gc_alloc(nelem * size, gc);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, (nelem * size));
	return (arr);
}
