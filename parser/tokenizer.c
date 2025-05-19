// #include "minishell.h"
#include "../minishell.h"

t_token	*add_token(t_token *last, char *value, t_gc **gc)
{
	t_token *new = gc_alloc(sizeof(t_token), gc);
	new->value = value;
	new->next = NULL;
	if (last)
		last->next = new;
	return new;
}

// t_token	*tokenize(const char *input, t_gc **gc) // ls | cat > ls | echo "hello" | grep hello 
// {
// 	int		i = 0;
// 	t_token	*head = NULL;
// 	t_token	*last = NULL;

// 	while (input[i])
// 	{
// 		while (ft_isspace(input[i])) // skip space
// 			i++;
// 		if (input[i] == '\'' || input[i] == '"') // ""
// 		{
// 			char	quote = input[i++]; // ""
// 			int		start = i;
// 			while (input[i] && input[i] != quote)
// 				i++;
// 			char	*val = ft_substr_gc(input, start, i - start, gc);
// 			last = add_token(last, val, gc);
// 			if (!head)
// 				head = last;
// 			if (input[i])
// 				i++;
// 		}
// 		else if (is_operator(input[i]))
// 		{
// 			int	start = i;
// 			if ((input[i] == '>' || input[i] == '<') && input[i] == input[i+1])
// 				i += 2;
// 			else
// 				i++;
// 			char	*val = ft_substr_gc(input, start, i - start, gc);
// 			last = add_token(last, val, gc);
// 			if (!head)
// 				head = last;
// 		}
// 		else if (input[i])
// 		{
// 			int	start = i;
// 			while (input[i] && !ft_isspace(input[i]) && !is_operator(input[i]) 
// 				&& input[i] != '\'' && input[i] != '"')
// 					i++;
// 			char	*val = ft_substr_gc(input, start, i - start, gc);
// 			last = add_token(last, val, gc);
// 			if (!head)
// 				head = last;
// 		}
// 	}
// 	return (head);
// }

t_token	*tokenize(const char *input, t_gc **gc)
{
	int		i = 0;
	t_token	*head = NULL;
	t_token	*last = NULL;

	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;

		if (input[i] == '\'' || input[i] == '"') // quote
		{
			char	quote = input[i];
			int		start = i++; // include the opening quote
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
				i++; // include the closing quote
			else
			{
				write(2, "parse error: unclosed quote\n", 29);
				return (NULL);
			}
			char *val = ft_substr_gc(input, start, i - start, gc); // include quotes
			last = add_token(last, val, gc);
			if (!head)
				head = last;
		}
		else if (is_operator(input[i])) // | > >> < <<
		{
			int	start = i;
			if ((input[i] == '>' || input[i] == '<') && input[i] == input[i + 1])
				i += 2;
			else
				i++;
			char *val = ft_substr_gc(input, start, i - start, gc);
			last = add_token(last, val, gc);
			if (!head)
				head = last;
		}
		else if (input[i]) // word
		{
			int	start = i;
			while (input[i] && !ft_isspace(input[i]) && !is_operator(input[i]) && input[i] != '\'' && input[i] != '"')
				i++;
			char *val = ft_substr_gc(input, start, i - start, gc);
			last = add_token(last, val, gc);
			if (!head)
				head = last;
		}
	}
	return head;
}
