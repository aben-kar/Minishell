/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:48:20 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/24 20:48:21 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

#include "../minishell.h"
typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

void	*gc_alloc(size_t size, t_gc **gc);
void	gc_free_all(t_gc **gc);

#endif
