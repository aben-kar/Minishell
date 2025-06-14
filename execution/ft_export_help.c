/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:08:15 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/14 19:30:00 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	alpha(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if ((args[i] >= 'a' && args[i] <= 'z')
			|| (args[i] >= 'A' && args[i] <= 'Z'))
			return (1);
		i++;
	}
	return (0);
}

void	print_error(char *key, t_gc **gc)
{
	char	*error_1;
	char	*error_2;

	error_1 = ft_strjoin_gc("export: ", key, gc);
	error_2 = ft_strjoin_gc(error_1, ": not a valid identifier", gc);
	ft_putendl_fd(error_2, 1);
	g_exit_status = 1;
}

int	count_plus(char *arg)
{
	char	*equal;
	int		plus_count;
	int		i;

	if (!arg || !arg[0])
		return (0);
	equal = ft_strchr(arg, '=');
	plus_count = 0;
	i = 0;
	while (arg[i] && (&arg[i]) < equal)
	{
		if (arg[i] == '+')
			plus_count++;
		i++;
	}
	return (plus_count);
}

int	equal_or_plus(char *arg)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (*(equal - 1) == '+')
	{
		if (count_plus(arg) > 1)
			return (2);
		return (1);
	}
	return (0);
}

bool	multiple_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}
