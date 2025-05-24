#include "../minishell.h"

void	*gc_alloc(size_t size, t_gc **gc)
{
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
