/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:52:34 by aben-kar          #+#    #+#             */
/*   Updated: 2025/06/20 14:02:29 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	first_char(char *key)
{
	int	i;

	i = 0;
	if ((key[i] >= '0' && key[i] <= '9') || key[i] == 61)
		return (false);
	return (true);
}

char	*implement_key(char *args, t_gc **gc)
{
	char	*key;
	int		is_equal;
	char	*equal;
	int		position_equal;

	is_equal = equal_or_plus(args);
	equal = ft_strchr(args, '=');
	if (is_equal == 0)
	{
		position_equal = equal - args;
		key = ft_substr_gc(args, 0, position_equal, gc);
	}
	else
	{
		position_equal = equal - args - 1;
		key = ft_substr_gc(args, 0, position_equal, gc);
	}
	return (key);
}

char	*implement_value(char *args, t_gc **gc)
{
	char	*value;
	char	*equal;

	equal = ft_strchr(args, '=');
	if (*(equal + 1) == '\0')
		value = ft_strdup_gc("", gc);
	else
		value = ft_strdup_gc(equal + 1, gc);
	return (value);
}

void	key_with_equal(char *arg, t_vrr *var, t_env **env, t_gc **gc)
{
	t_env	*tmp;
	t_env	*repetition;

	tmp = *env;
	var->key = implement_key(arg, gc);
	if ((first_char(var->key) == false) || (check_key(var->key) == false))
	{
		print_error(var->key, gc);
		return ;
	}
	var->value = implement_value(arg, gc);
	repetition = *env;
	while (repetition)
	{
		if (ft_strcmp(repetition->key, var->key) == 0)
		{
			repetition->value = var->value;
			return ;
		}
		repetition = repetition->next;
	}
	insert_at_end(&tmp, var->key, var->value, gc);
}

void	key_with_plus(char *arg, t_vrr *var, t_env **env, t_gc **gc)
{
	t_env	*tmp;
	t_env	*repetition;
	char	*new_val;

	tmp = *env;
	var->key = implement_key(arg, gc);
	if ((first_char(var->key) == false) || (check_key(var->key) == false))
	{
		print_error(var->key, gc);
		return ;
	}
	var->value = implement_value(arg, gc);
	repetition = *env;
	while (repetition)
	{
		if ((ft_strcmp(repetition->key, var->key)) == 0)
		{
			new_val = ft_strjoin_gc(repetition->value, var->value, gc);
			repetition->value = new_val;
			return ;
		}
		repetition = repetition->next;
	}
	insert_at_end(&tmp, var->key, var->value, gc);
}
