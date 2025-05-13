/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_gc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:17:04 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/13 16:26:23 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

char	*ft_strdup_gc(const char *s1, t_gc **gc)
{
	char	*dest;
	size_t	i;

	i = 0;
	while (s1[i] != 0)
		i++;
	dest = gc_alloc((i + 1), gc);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
