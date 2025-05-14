/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copier_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:31 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/14 19:55:38 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

void ft_env_null(t_env **head)
{
    t_env *tmp = malloc(sizeof(t_env));

    if (!tmp)
        exit(1);

    tmp->key = ft_strdup("PWD");
    tmp->value = ft_strdup("/home/acben-ka/Desktop/allo");
    tmp->next = NULL;
    if (!*head)
    {
        *head = tmp;
        return;
    }
}

void insert_at_end(t_env **head, char *key, char *value) // char **env
{
    t_env *new_node = malloc(sizeof(t_env));

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

t_env *init_copier_env(char **envp)
{
    t_env *head = NULL;
    int i = 0;

    if (!*envp)
    {
        printf("testdadad\n");
        ft_env_null(&head);
        return head;
    }
    
    while (envp[i])
    {
        char *equal = ft_strchr(envp[i], '=');
        if (equal)
        {
            int key_len = equal - envp[i];
            char *key = ft_substr(envp[i], 0, key_len);
            char *value = ft_strdup(equal + 1); // '='

            insert_at_end(&head, key, value);
        }
        i++;
    }
    return head;
}

t_env *ft_copier_env(t_env *env, char **envp)
{
    env = init_copier_env(envp);
    return env;
    // return 0;
}


// PWD=/home/acben-ka/Desktop
// SHLVL=1
// _=/usr/bin/env
