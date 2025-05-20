/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:26:01 by achraf            #+#    #+#             */
/*   Updated: 2025/05/19 17:54:42 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void excute_external_cmd(t_command *cmd, t_env *env, t_gc **gc)
{
    char **copier_env = env_to_array(env, gc);
    char *cmd_path = find_executable_path(cmd, env, gc);
    int id = fork();
    if (id == 0)
    {
        signal(SIGINT, SIG_DFL); // TEST
        signal(SIGQUIT, SIG_DFL); // TEST
        execve(cmd_path, cmd->cmd, copier_env);

        perror("execve"); // exit status "TODO"
        exit(1); // NEW
    }
    else
    {
        signal(SIGINT, SIG_IGN); // TEST
        signal(SIGQUIT, SIG_IGN); // TEST
        waitpid(id, NULL, 0); // DYALK
        // int status;
        // waitpid(id, &status, 0);
        // if (status == 2 << 8)
        //     write(1, "\n", 1);
        setup_signals(); // TEST
    }
}

void built_in(t_command *cmd, t_env *env, t_gc **gc)
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
                ft_cd(cmd->cmd + 1, env, gc);
            else if ((ft_strcmp(cmd->cmd[0], "pwd")) == 0) // pwd
                ft_pwd();
            else if ((ft_strcmp(cmd->cmd[0], "env")) == 0) // env
                ft_env(env);
            else if ((ft_strcmp(cmd->cmd[0], "export")) == 0) // export
                ft_export(cmd->cmd + 1, &env, gc);
            else if ((ft_strcmp(cmd->cmd[0], "unset")) == 0) // unset
                ft_unset(cmd->cmd + 1, &env);
            else if ((ft_strcmp(cmd->cmd[0], "exit")) == 0) // exit
                ft_exit(cmd->cmd + 1, gc);
            break;
        }
        j++;
    }
    if (found == 0)
    {
        ft_putstr_fd(cmd->cmd[0], 2);
        ft_putendl_fd(": command not found", 2);
        // exit status "TODO"
    }
}