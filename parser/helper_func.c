// #include "minishell.h"
#include "../minishell.h"

int	is_redir(char *s)
{
	return (!ft_strcmp(s, ">") || !ft_strcmp(s, "<") 
		|| !ft_strcmp(s, "<<") || !ft_strcmp(s, ">>"));
}

int	redir_type(char	*s)
{
	if (!ft_strcmp(s, ">"))
		return REDIR_OUT;
	if (!ft_strcmp(s, ">>"))
		return REDIR_APPEND;
	if (!ft_strcmp(s, "<"))
		return REDIR_IN;
	return REDIR_HEREDOC; // "<<"
}

int	ft_isspace(char c)
{
	return (c == ' ');
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return 1;
	return 0;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
