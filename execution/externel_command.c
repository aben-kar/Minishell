/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externel_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:21:38 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/16 01:31:58 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

char **get_path(t_env *envp, t_gc **gc)
{
    char *found;
    char **split_path;
    t_env *tmp;

    tmp = envp;
    
    char **copier_env = env_to_array(tmp, gc);
    while (*copier_env)
    {
        found = ft_strnstr(*copier_env, "PATH=", 5);
        if (found)
        {
            split_path = ft_split_gc(found + 5, ":", gc);
            if (!split_path)
            {
                write(2, "PATH Not Found In Environment./n", 31);
                return (NULL);
            }
            return (split_path);
        }
        copier_env++;
    }
    return (NULL);
}

bool check_command(t_command *check, t_env *envp, t_gc **gc)
{
    t_env *tmp;
    tmp = envp;
    
    if (!check || !check->cmd || !check->cmd[0])
        return (false);

    char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int j = 0;

    while (builtins[j])
    {
        if ((ft_strncmp(check->cmd[0], builtins[j], ft_strlen(builtins[j]))) == 0)
            return (false);
        j++;
    }

    if ((access(check->cmd[0], F_OK | X_OK)) == 0) // ls
        return (true);

    char **directory = get_path(tmp, gc);
    if (!directory)
        return (false);

    int i = 0;
    while (directory[i])
    {
        char *add_slash = ft_strjoin_gc(directory[i], "/", gc);
        char *cmd_path = ft_strjoin_gc(add_slash, check->cmd[0], gc);
        if ((access(cmd_path, F_OK | X_OK)) == 0)
            return (true);
        i++;
    }

    return (false);
}


char *find_executable_path(t_command *shell, t_env *envp, t_gc **gc)
{
    if ((access(shell->cmd[0], F_OK | X_OK)) == 0) // execute direct "/bin/ls"
        return (*(shell->cmd));                    // External Commands
    char **directory = get_path(envp, gc);
    int i = 0;
    while (directory[i])
    {
        char *add_slash = ft_strjoin_gc(directory[i], "/", gc);
        char *cmd_path = ft_strjoin_gc(add_slash, shell->cmd[0], gc);
        if ((access(cmd_path, F_OK | X_OK)) == 0)
            return (cmd_path); // External Commands
        i++;
    }
    return (NULL);
}

void execute_command(t_command *shell, t_env *env, t_gc **gc)
{
    if (check_command(shell, env, gc) == true) // external command
        excute_extenel_cmd(shell, env, gc);
    
    else // Built-in
        built_in(shell, env, gc);
}