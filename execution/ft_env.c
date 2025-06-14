/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:09:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/14 18:30:46 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

int	ft_env(t_env *env)
{
	t_env	*envp;

	envp = env;
	while (envp)
	{
		if (envp->key && envp->value)
		{
			ft_putstr_fd(envp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(envp->value, 1);
		}
		envp = envp->next;
	}
	return (0);
}
