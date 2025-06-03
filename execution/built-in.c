/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:42:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/03 00:58:05 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

bool check_command(t_command *cmd)
{
    if (!cmd || !cmd->cmd || !cmd->cmd[0])
        return false;
    int i = 0;

    char *built_in[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

    while (built_in[i])
    {
        if ((ft_strncmp(cmd->cmd[0], built_in[i], ft_strlen(built_in[i]))) == 0)
            return (false);
        i++;
    }
    return (true);
}

void handle_builtin_redirection(t_command *cmd, int *save_in, int *save_out, int setup)
{
    if (setup)
    {
        *save_in = dup(STDIN_FILENO);
        *save_out = dup(STDOUT_FILENO);
        handel_redirection_1(cmd);
    }
    else
    {
        if (*save_in != -1)
        {
            dup2(*save_in, STDIN_FILENO);
            close(*save_in);
        }
        if (*save_out != -1)
        {
            dup2(*save_out, STDOUT_FILENO);
            close(*save_out);
        }
    }
}

int execute_builtin_command(t_command *cmd, t_env **env, t_gc **gc)
{
    char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int j = -1;

    while (builtins[++j])
    {
        if ((ft_strcmp(cmd->cmd[0], builtins[j])) == 0)
        {
            if ((ft_strcmp(cmd->cmd[0], "echo") == 0))
                return ft_echo(cmd->cmd + 1);
            else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
                return ft_cd(cmd->cmd + 1, *env, gc);
            else if ((ft_strcmp(cmd->cmd[0], "pwd")) == 0)
                return ft_pwd();
            else if ((ft_strcmp(cmd->cmd[0], "env")) == 0)
                return ft_env(*env);
            else if ((ft_strcmp(cmd->cmd[0], "export")) == 0)
                return (ft_export(cmd->cmd + 1, env, gc), g_exit_status);
            else if ((ft_strcmp(cmd->cmd[0], "unset")) == 0)
                return ft_unset(cmd->cmd + 1, env);
            else if ((ft_strcmp(cmd->cmd[0], "exit")) == 0)
                return ft_exit(cmd->cmd + 1, gc);
        }
    }
    write_error(cmd->cmd[0], 2);
    return 127; // Command not found
}

void built_in(t_command *cmd, t_env **env, t_gc **gc)
{
    int save_in = -1;
    int save_out = -1;

    if (cmd->has_redirect)
        handle_builtin_redirection(cmd, &save_in, &save_out, 1);

    g_exit_status = execute_builtin_command(cmd, env, gc);

    if (cmd->has_redirect)
        handle_builtin_redirection(cmd, &save_in, &save_out, 0);
}