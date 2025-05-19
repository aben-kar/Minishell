#include "../minishell.h"

char	*ft_strjoin_char_gc(const char *s, char c, t_gc **gc)
{
	char	*result;
	int		len;
	int		i;

	if (!s)
		len = 0;
	else
		len = ft_strlen(s);

	result = gc_alloc(sizeof(char) * (len + 2), gc);
	if (!result)
		return (NULL);

	i = 0;
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i++] = c;
	result[i] = '\0';

	return (result);
}
