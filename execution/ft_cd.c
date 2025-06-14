/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:21:32 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/14 18:15:35 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

int	ft_cd(char **args, t_env *env, t_gc **gc)
{
	if (args[0] && args[1])
	{
		ft_putendl_fd("cd: too many arguments", 1);
		return (1);
	}
	if (!args[0] || ((ft_strcmp(args[0], "~")) == 0))
		return (handle_home_cd(env));
	if (validate_path(args[0]) != 0)
		return (1);
	return (change_directory(args[0], &env, gc));
}
