/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:21:32 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/23 23:37:46 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

char *print_home(t_env *env)
{
    t_env *tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, "HOME") == 0)
        {
            char *str = tmp->value;
            return str; // kayena l HOME
        }
        tmp = tmp->next;
    }
    return NULL; // No HOME.
}

void update_pwd_oldpwd(char *oldpwd, t_env **env, t_gc **gc)
{
    t_env *current = *env;
    char *newpwd = getcwd(NULL, 0);

    // Update OLDPWD
    while (current)
    {
        if (ft_strcmp(current->key, "OLDPWD") == 0)
        {
            // free(current->value);
            current->value = ft_strdup_gc(oldpwd, gc);
            break;
        }
        current = current->next;
    }

    // Update PWD
    current = *env;
    while (current)
    {
        if (ft_strcmp(current->key, "PWD") == 0)
        {
            // free(current->value);
            current->value = ft_strdup_gc(newpwd, gc);
            break;
        }
        current = current->next;
    }
    free(newpwd);
}

int ft_cd(char **args, t_env *env, t_gc **gc)
{
    t_stat info;
    t_env *tmp = env;
    if (args[0] && args[1])
    {
        ft_putendl_fd("cd: too many arguments", 1);
        return 1;
    }
    if (!args[0] || ((ft_strcmp(args[0], "~")) == 0)) // just "cd" go to home
    {
        char *to_home = print_home(tmp);
        if (!to_home)
        {
            ft_putendl_fd("cd: HOME not set", 2);
            return 1;
        }
        else if (chdir(to_home) == -1)
        {
            perror("cd");
            return 1;
        }
    }

    else if (args[0])
    {
        if ((stat(args[0], &info)) == 0) // check is valide name
        {
            if (S_ISDIR(info.st_mode)) // chaeck is a directory
            {
                char *oldpwd = getcwd(NULL, 0);
                if (chdir(args[0]) != 0)
                {
                    ft_putendl_fd("cd: Permission denied", 1);
                    free(oldpwd);
                    return 1;
                }
                char *new_pwd = getcwd(NULL, 0);
                if (!new_pwd)
                {
                    ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 1);
                    free(oldpwd);
                    return 1;
                }

                update_pwd_oldpwd(oldpwd, &env, gc);
                free(new_pwd);
                free(oldpwd);
            }
            else // is file
            {
                ft_putendl_fd("cd: Not a directory", 1);
                return 1;
            }
        }
        else // no valide name
        {
            ft_putendl_fd("cd: No such file or directory", 1);
            return 1;
        }
    }
    return (0);
}
