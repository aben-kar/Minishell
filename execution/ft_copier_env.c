/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copier_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:31 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/24 02:02:58 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

void ft_env_null(t_env **head, t_gc **gc)
{
    t_env *tmp = gc_alloc(sizeof(t_env), gc);

    if (!tmp)
        exit(1);
    char *pwd = getcwd(NULL, 0);
    insert_at_end(head, ft_strdup_gc("PWD", gc), ft_strdup_gc(pwd, gc), gc);
    insert_at_end(head, ft_strdup_gc("SHLVL", gc), ft_strdup_gc("1", gc), gc);
    insert_at_end(head, ft_strdup_gc("_", gc), ft_strdup_gc("/usr/bin/env", gc), gc);
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
        return;
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

            if (ft_strcmp(key, "SHLVL") == 0)
            {
                int shlvl = 1;
                if (*(equal + 1) != '\0')
                    shlvl = ft_atoi(equal + 1) + 1;
                char *shlvl_str = ft_itoa(shlvl);
                char *value = ft_strdup_gc(shlvl_str, gc);
                free(shlvl_str);
                insert_at_end(&head, key, value, gc);
            }
            else
            {
                char *value = ft_strdup_gc(equal + 1, gc);
                insert_at_end(&head, key, value, gc);
            }
        }
        i++;
    }
    return head;
}

// PWD=/home/acben-ka/Desktop
// SHLVL=1
// _=/usr/bin/env
