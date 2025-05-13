/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:12 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/13 16:25:48 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

char **env_to_array(t_env *env)
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

    envp = malloc(sizeof(char *) * (size + 1));
    if (!envp)
        return NULL;

    tmp = env;
    i = 0;
    while (tmp)
    {
        char *key_equal = ft_strjoin(tmp->key, "=");
        envp[i] = ft_strjoin(key_equal, tmp->value);
        free(key_equal);
        tmp = tmp->next;
        i++;
    }

    envp[i] = NULL;

    return envp;
}
