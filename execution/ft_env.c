/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:09:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/14 19:53:55 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

int ft_env(t_env *env)
{
    // if (!env)
    // {
    //     char *pwd = getcwd(NULL, 0);
    //     ft_putstr_fd("PWD=", 1);
    //     ft_putendl_fd(pwd, 1);
    //     ft_putendl_fd("SHLVL=1", 1);
    //     ft_putendl_fd("_=/usr/bin/env", 1);
    // }

    t_env *envp = env;

    while (envp)
    {
        if (envp->key && envp->value) // katcheki wach key-> gedameha value bach t printih.
        {
            ft_putstr_fd(envp->key, 1);
            ft_putstr_fd("=", 1);
            ft_putendl_fd(envp->value, 1);
        }
        envp = envp->next;
    }
    return (0);
}