#include "../minishell.h"

t_token	*add_token(t_token *last, char *value, t_gc **gc)
{
	t_token	*new;

	new = NULL;
	new = gc_alloc(sizeof(t_token), gc);
	new->value = value;
	new->next = NULL;
	if (last)
		last->next = new;
	return (new);
}

t_token	*tokenize(const char *input, t_gc **gc)
{
	int		i;
	t_token	*head;
	t_token	*last;
	char	*val;
	int		start;
	char	quote;

	i = 0;
	head = NULL;
	last = NULL;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			start = i++;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
				i++;
			else
			{
				bash_unclosed_quote_error(quote);
				return (NULL);
			}
			val = ft_substr_gc(input, start, i - start, gc);
			last = add_token(last, val, gc);
			if (!head)
				head = last;
		}
		else if (is_operator(input[i]))
		{
			start = i;
			if ((input[i] == '>' || input[i] == '<') && input[i] == input[i + 1])
				i += 2;
			else
				i++;
			val = ft_substr_gc(input, start, i - start, gc);
			last = add_token(last, val, gc);
			if (!head)
				head = last;
		}
		else if (input[i])
		{
			start = i;
			while (input[i] && !ft_isspace(input[i]) && !is_operator(input[i]) && input[i] != '\'' && input[i] != '"')
				i++;
			val = ft_substr_gc(input, start, i - start, gc);
			last = add_token(last, val, gc);
			if (!head)
				head = last;
		}
	}
	return (head);
}
