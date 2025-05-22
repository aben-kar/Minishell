/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:26:01 by achraf            #+#    #+#             */
/*   Updated: 2025/05/22 01:32:20 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void excute_external_cmd(t_command *cmd, t_env *env, t_gc **gc)
{
    char **copier_env = env_to_array(env, gc);
    char *cmd_path = find_executable_path(cmd, env, gc);
    int status;
    if (!cmd_path)
    {
        g_exit_status = 127;
        return;
    }
    int id = fork();
    if (id == 0)
    {
        signal(SIGINT, SIG_DFL); // TEST
        signal(SIGQUIT, SIG_DFL); // TEST
        if (cmd->has_redirect)
        {
            t_redirect *redir = cmd->redirects;
            while (redir)
            {
                if (redir->type == REDIR_IN) // "<" read 
                {
                    int in_fd = open(redir->filename, O_RDONLY);
                    if (in_fd < 0)
                    {
                        perror("open");
                        exit(1);
                    }
                    dup2(in_fd, STDIN_FILENO);
                    close(in_fd);
                }
                else if (redir->type == REDIR_OUT) // '>' out
                {
                    int out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (out_fd < 0)
                    {
                        perror("open");
                        exit(1);
                    }
                    dup2(out_fd, STDOUT_FILENO);
                    close(out_fd);
                }
                else if (redir->type == REDIR_APPEND) // '>>' append
                {
                    int append_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    if (append_fd < 0)
                    {
                        perror("open");
                        exit(1);
                    }
                    dup2(append_fd, STDOUT_FILENO);
                    close(append_fd);
                }
                redir = redir->next;
            }
        }
        if (execve(cmd_path, cmd->cmd, copier_env) == -1)
        {
            // perror("execve"); // exit status "TODO"
            exit(127); // NEW
        }

    }
    else
    {
        signal(SIGINT, SIG_IGN); // TEST
        signal(SIGQUIT, SIG_IGN); // TEST
        waitpid(id, &status, 0);
        if (WIFEXITED(status))
        {
            printf ("1\n");
            g_exit_status = WEXITSTATUS(status);
            if (g_exit_status == 126)
                write_error(cmd->cmd[0], 1);
        }
        else if (WIFSIGNALED(status))
        {
            g_exit_status = 128 + WTERMSIG(status);
            if (g_exit_status == 131)
            {
                write (1, "quit (core dumped)\n", ft_strlen("quit (core dumped)\n"));  
            }
            else if(g_exit_status == 130)
                write(1, "\n", 1);
        }
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
                g_exit_status = 0;
            }
            else if (ft_strcmp(cmd->cmd[0], "cd") == 0) // cd
                ft_cd(cmd->cmd + 1, env, gc);
            else if ((ft_strcmp(cmd->cmd[0], "pwd")) == 0) // pwd
            {
                ft_pwd();
                g_exit_status = 0;
            }
            else if ((ft_strcmp(cmd->cmd[0], "env")) == 0) // env
            {
                ft_env(env);
                g_exit_status = 0;
            }
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
        write_error(cmd->cmd[0], 2);
        g_exit_status = 127; // Command not found
    }
}