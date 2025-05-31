/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:50:45 by aben-kar          #+#    #+#             */
/*   Updated: 2025/05/31 07:35:41 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

// algorithme deyal unset

int find_position(char *key, t_env *env)
{
    t_env *tmp = env;

    int i = 1;
    while (tmp)
    {
        if ((ft_strcmp(key, tmp->key)) == 0)
        {
            return i;
        }
        tmp = tmp->next;
        i++;
    }
    return 0;
}

void deleteNode(t_env **head, int position)
{
    if (!head || !*head)
        return;
    t_env *temp = *head;
    
    if (position == 1)
    {
        *head = temp->next;
        return;
    }
    
    int i = 1;
    t_env *prev = NULL;
    while (temp != NULL && i < position)
    {
        prev = temp;
        temp = temp->next;
        i++;
    }
    if (temp != NULL)
    {
        prev->next = temp->next;
    }
}

int ft_unset(char **args, t_env **env)
{
    if (!args || !env || !*env)
        return 0;
    int i = 0;
    while (args[i])
    {
        int position = find_position(args[i], *env);
        if (position != 0)
            deleteNode(env, position);
        i++;
    }
    return 0;
}
