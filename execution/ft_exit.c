/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:42:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/14 18:35:01 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

bool	all_is_digit(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] == '\0')
		return (false);
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

void	handle_non_numeric_arg(char *arg, t_gc **gc)
{
	char	*join;

	ft_putendl_fd("exit", 1);
	ft_putstr_fd("exit: ", 1);
	join = ft_strjoin_gc(arg, ": numeric argument required", gc);
	ft_putendl_fd(join, 1);
	exit(2);
}

int	handle_too_many_args(void)
{
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("exit: ", 1);
	ft_putendl_fd("too many arguments", 1);
	return (1);
}

void	handle_valid_exit(char *arg, t_gc **gc)
{
	long long	nbr;
	char		*join;

	nbr = ft_aatoi(arg);
	if (nbr == LLONG_MAX || nbr == LLONG_MIN)
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("exit: ", 1);
		join = ft_strjoin_gc(arg, ": numeric argument required", gc);
		ft_putendl_fd(join, 1);
		exit(2);
	}
	ft_putendl_fd("exit", 1);
	exit(nbr);
}

int	ft_exit(char **args, t_gc **gc)
{
	if (!args || !*args)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (!all_is_digit(args[0]))
		handle_non_numeric_arg(args[0], gc);
	else if (args[1])
		return (handle_too_many_args());
	else if (*args)
		handle_valid_exit(args[0], gc);
	return (0);
}
