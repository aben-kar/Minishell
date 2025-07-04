/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copier_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:31 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/22 15:31:05 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_copier_env(char **envp, t_gc **gc)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = 0;
	if (!*envp)
	{
		ft_env_null(&head, gc);
		return (head);
	}
	while (envp[i])
	{
		process_env_line(&head, envp[i], gc);
		i++;
	}
	return (head);
}
