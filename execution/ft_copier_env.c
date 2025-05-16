/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copier_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:31 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/16 01:28:44 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

void ft_env_null(t_env **head, t_gc **gc)
{
    t_env *tmp = gc_alloc(sizeof(t_env), gc);

    if (!tmp)
        exit(1);

    tmp->key = ft_strdup_gc("PWD", gc);
    tmp->value = ft_strdup_gc("/home/acben-ka/Desktop/allo", gc);
    tmp->next = NULL;
    if (!*head)
    {
        *head = tmp;
        return;
    }
}

void insert_at_end(t_env **head, char *key, char *value, t_gc **gc) // char **env
{
    t_env *new_node = gc_alloc(sizeof(t_env), gc);

    if (!new_node)
        exit(1);
    
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    
    if (!*head)
    {
        *head = new_node;
        return ;
    }
    
    t_env *temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;

    // return head;
}

t_env *init_copier_env(char **envp, t_gc **gc)
{
    t_env *head = NULL;
    int i = 0;

    if (!*envp)
    {
        ft_env_null(&head, gc);
        return head;
    }
    
    while (envp[i])
    {
        char *equal = ft_strchr(envp[i], '=');
        if (equal)
        {
            int key_len = equal - envp[i];
            char *key = ft_substr_gc(envp[i], 0, key_len, gc);
            char *value = ft_strdup_gc(equal + 1, gc); // '='

            insert_at_end(&head, key, value, gc);
        }
        i++;
    }
    return head;
}

t_env *ft_copier_env(t_env *env, char **envp, t_gc **gc)
{
    env = init_copier_env(envp, gc);
    return env;
    // return 0;
}


// PWD=/home/acben-ka/Desktop
// SHLVL=1
// _=/usr/bin/env
