#include "../minishell.h"

char	*ft_strndup(const char *s, size_t n, t_gc **gc)
{
    size_t	i;
    char	*dup;

	i = 0;
    while (s[i] && i < n)
        i++;
    dup = gc_alloc((i + 1), gc);
    if (!dup)
        return (NULL);
    for (size_t j = 0; j < i; j++)
        dup[j] = s[j];
    dup[i] = '\0';
    return (dup);
}
