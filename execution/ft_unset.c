/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:50:45 by aben-kar          #+#    #+#             */
/*   Updated: 2025/06/22 15:31:26 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_position(char *key, t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 1;
	while (tmp)
	{
		if ((ft_strcmp(key, tmp->key)) == 0)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

void	delete_node(t_env **head, int position)
{
	t_env	*temp;
	t_env	*prev;
	int		i;

	if (!head || !*head)
		return ;
	temp = *head;
	if (position == 1)
	{
		*head = (*head)->next;
		return ;
	}
	i = 1;
	prev = NULL;
	while (temp != NULL && i < position)
	{
		prev = temp;
		temp = temp->next;
		i++;
	}
	prev->next = temp->next;
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	position;

	if (!args || !env || !*env)
		return (0);
	i = 0;
	while (args[i])
	{
		position = find_position(args[i], *env);
		if (position)
			delete_node(env, position);
		i++;
	}
	return (0);
}
