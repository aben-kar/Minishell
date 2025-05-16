/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:12 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/16 01:23:39 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

char **env_to_array(t_env *env, t_gc **gc)
{
    int i = 0;
    t_env *tmp = env;
    int size = 0;
    char **envp;
    
    while (tmp)
    {
        size++;
        tmp = tmp->next;
    }

    envp = gc_alloc(sizeof(char *) * (size + 1), gc);
    if (!envp)
        return NULL;

    tmp = env;
    i = 0;
    while (tmp)
    {
        envp[i] = ft_strjoin_gc(ft_strjoin_gc(tmp->key, "=", gc), tmp->value, gc);
        // free(key_equal);
        tmp = tmp->next;
        i++;
    }
    envp[i] = NULL;

    return envp;
}
