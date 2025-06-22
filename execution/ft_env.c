/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:09:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/22 15:31:12 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
