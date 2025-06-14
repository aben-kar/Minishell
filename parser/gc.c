/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:47:51 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/08 17:36:53 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*gc_alloc(size_t size, t_gc **gc)
{
	if (!gc)
		return NULL;
	void	*ptr;
	t_gc	*new;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new = malloc(sizeof(t_gc));
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	new->ptr = ptr;
	new->next = *gc;
	*gc = new;
	return (ptr);
}

void	gc_free_all(t_gc **gc)
{
	t_gc	*tmp;

	while (*gc)
	{
		tmp = *gc;
		*gc = (*gc)->next;
		free(tmp->ptr);
		free(tmp);
	}
}
