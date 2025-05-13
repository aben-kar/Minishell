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