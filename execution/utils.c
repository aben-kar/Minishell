/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:12 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/12 19:08:10 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

char **env_to_array(t_env *env, t_gc **gc)
{
    int i;
    t_env *tmp = env;
    int size = 0;
    char **envp;

    if (!env || !gc)
        return (NULL);
    
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
        tmp = tmp->next;
        i++;
    }
    envp[i] = NULL;

    return envp;
}
void write_error(char *cmd, int error_code)
{
    if (!cmd)
        return ;
    
    if (error_code == 6)
    {
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": ambiguous redirect\n", 2);
    }
    
    else if (error_code == 5) // No such file or directory
    {
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        g_exit_status = 1;
    }
    else if (error_code == 4)
    {
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": syntax error near unexpected token `)'\n", 2);
        g_exit_status = 2;
    }   
    else if (error_code == 3)
    {
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": is a directory\n", 2);
        g_exit_status = 126; // Is a directory
    }
    else if (error_code == 2) // Command not found
    {
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": command not found\n", 2);
        g_exit_status = 127;
    }
    else if (error_code == 1) // Permission denied
    {
        // printf ("2\n");
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": Permission denied\n", 2);
        g_exit_status = 126;
    }
    else if (error_code == 0) // No such file or directory
    {
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        g_exit_status = 127;
    }
}
