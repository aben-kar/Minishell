/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:21:38 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/24 00:12:31 by achraf           ###   ########.fr       */
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

char *find_executable_path(t_command *shell, t_env *envp, t_gc **gc)
{
    if (!shell->cmd || !shell->cmd[0] || !shell->cmd[0][0])
    {
        printf("empty cmd\n");
        return NULL;
    }
    
    if (ft_strchr(shell->cmd[0], '/'))
    {
        if (access(shell->cmd[0], F_OK) != 0)
        {
            write_error(shell->cmd[0], 0); // No such file or directory
            return NULL;
        }
        if (access(shell->cmd[0], X_OK) != 0)
        {
            write_error(shell->cmd[0], 1); // Permission denied
            return NULL;
        }
        return shell->cmd[0];
    }
    
    char **directory = get_path(envp, gc);
    if (!directory)
    {
        write_error(shell->cmd[0], 2); // Command not found
        return NULL;
    }
    
    int i = 0;
    while (directory[i])
    {
        char *add_slash = ft_strjoin_gc(directory[i], "/", gc);
        char *cmd_path = ft_strjoin_gc(add_slash, shell->cmd[0], gc);
        
        if (access(cmd_path, F_OK) == 0)
        {
            // Check ila executable
            if (access(cmd_path, X_OK) == 0)
                return cmd_path;
            else
            {
                // File kayf walakin ma executable
                write_error(shell->cmd[0], 1); // Permission denied
                return NULL;
            }
        }
        i++;
    }
    write_error(shell->cmd[0], 2); // Command not found
    return NULL;
}

bool check_command(t_command *cmd)
{
    t_command *tmp = cmd;
    int i = 0;
    
    char *built_in[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

    while(built_in[i])
    {
        if ((ft_strncmp(tmp->cmd[0], built_in[i], ft_strlen(built_in[i]))) == 0)
            return (false);
        i++;
    }
    return (true);
    
}

void execute_command(t_command *shell, t_env *env, t_gc **gc)
{
    if (check_command(shell) == true) // external command
    {
        excute_external_cmd(shell, env, gc);
    }
    
    else if (check_command(shell) == false)
        built_in(shell, env, gc);
}
