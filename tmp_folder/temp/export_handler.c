#include "../minishell.h"

int	contains_equal(const char *input, int *i)
{
	int	eq_index;

	eq_index = -1;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '=' && eq_index == -1)
			eq_index = *i;
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!skip_quoted(input, i))
				return (-2);
		}
		else
			(*i)++;
	}
	return (eq_index);
}

bool	skip_post_equal(const char *input, int *i)
{
	while (ft_isspace(input[*i]))
		(*i)++;
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!skip_quoted(input, i))
				return (false);
		}
		else
			(*i)++;
	}
	return (true);
}

char	*extract_token_value(const char *input, int start, int end, t_gc **gc)
{
	return (ft_substr_gc(input, start, end - start, gc));
}
