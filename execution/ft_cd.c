/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:21:32 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/02 15:47:19 by achraf           ###   ########.fr       */
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

    while (current)
    {
        if (ft_strcmp(current->key, "OLDPWD") == 0)
        {
            current->value = ft_strdup_gc(oldpwd, gc);
            break;
        }
        current = current->next;
    }

    current = *env;
    while (current)
    {
        if (ft_strcmp(current->key, "PWD") == 0)
        {
            current->value = ft_strdup_gc(newpwd, gc);
            break;
        }
        current = current->next;
    }
    free(newpwd);
}

int handle_home_cd(t_env *env)
{
    char *to_home = print_home(env);
    
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
    return 0;
}

int validate_path(char *path)
{
    t_stat info;
    
    if ((stat(path, &info)) != 0)
    {
        ft_putendl_fd("cd: No such file or directory", 1);
        return 1;
    }
    
    if (!S_ISDIR(info.st_mode))
    {
        ft_putendl_fd("cd: Not a directory", 1);
        return 1;
    }
    return 0;
}

int change_directory(char *path, t_env **env, t_gc **gc)
{
    char *oldpwd = getcwd(NULL, 0);
    
    if (chdir(path) != 0)
    {
        ft_putendl_fd("cd: Permission denied", 1);
        free(oldpwd);
        return 1;
    }
    
    char *new_pwd = getcwd(NULL, 0);
    if (!new_pwd || !oldpwd)
    {
        ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 1);
        free(oldpwd);
        return 1;
    }
    
    update_pwd_oldpwd(oldpwd, env, gc);
    free(new_pwd);
    free(oldpwd);
    return 0;
}

int ft_cd(char **args, t_env *env, t_gc **gc)
{
    if (args[0] && args[1])
    {
        ft_putendl_fd("cd: too many arguments", 1);
        return 1;
    }
    
    if (!args[0] || ((ft_strcmp(args[0], "~")) == 0))
    {
        return handle_home_cd(env);
    }
    
    if (validate_path(args[0]) != 0)
        return 1;
        
    return change_directory(args[0], &env, gc);
}
