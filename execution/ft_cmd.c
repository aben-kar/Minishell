/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:26:01 by achraf            #+#    #+#             */
/*   Updated: 2025/05/15 22:30:04 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void excute_extenel_cmd(t_command *cmd, t_env *env)
{
    char **copier_env = env_to_array(env);
    char *cmd_path = find_executable_path(cmd, env);
    int id = fork();
    if (id == 0)
    {
        // apply_redirections(cmd);
        execve(cmd_path, cmd->cmd, copier_env);
        exit(1);
    }
    else
        waitpid(id, NULL, 0);
}

void built_in(t_command *cmd, t_env *env)
{
    char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int j = 0;
    int found = 0;

    while (builtins[j])
    {
        if ((ft_strcmp(cmd->cmd[0], builtins[j])) == 0)
        {
            found = 1;
            if ((ft_strcmp(cmd->cmd[0], "echo") == 0)) // echo
            {
                ft_echo(cmd->cmd + 1);
            }

            else if (ft_strcmp(cmd->cmd[0], "cd") == 0) // cd
                ft_cd(cmd->cmd + 1, env);
            else if ((ft_strcmp(cmd->cmd[0], "pwd")) == 0) // pwd
                ft_pwd();
            else if ((ft_strcmp(cmd->cmd[0], "env")) == 0) // env
                ft_env(env);
            else if ((ft_strcmp(cmd->cmd[0], "export")) == 0) // export
                ft_export(cmd->cmd + 1, &env);
            else if ((ft_strcmp(cmd->cmd[0], "unset")) == 0) // unset
                ft_unset(cmd->cmd + 1, &env);
            else if ((ft_strcmp(cmd->cmd[0], "exit")) == 0) // exit
                ft_exit(cmd->cmd + 1);
            break;
        }
        j++;
    }
    if (!found)
    {
        char *error_echo = ft_strjoin(cmd->cmd[0], ": command not found");
        ft_putendl_fd(error_echo, 1);
    }
}