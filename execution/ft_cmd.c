/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:26:01 by achraf            #+#    #+#             */
/*   Updated: 2025/05/30 04:15:41 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int contains_space(char *str)
{
    while (*str)
    {
        if (*str == ' ')
            return 1;
        str++;
    }
    return 0;
}
void excute_external_cmd(t_command *cmd, t_env *env, t_gc **gc)
{
    char **copier_env = env_to_array(env, gc);
    char *cmd_path = find_executable_path(cmd, env, gc);

    // Ila mal9nach l command, l exit status deja set f find_executable_path
    if (!cmd_path)
        return; // Hir return bla matset g_exit_status merra khra

    int id = fork();
    if (id == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        // Handle redirections
        if (cmd->has_redirect)
        {
            t_redirect *redir = cmd->redirects;
            while (redir)
            {
                if (redir->type == REDIR_IN)
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
                else if (redir->type == REDIR_OUT)
                {
                    if (!redir->filename || !redir->filename[0] || contains_space(redir->filename))
                    {
                        ft_putendl_fd("ambiguous redirect", 2);
                        exit(1);
                    }
                    int out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (out_fd < 0)
                    {
                        perror("open");
                        exit(1);
                    }
                    dup2(out_fd, STDOUT_FILENO);
                    close(out_fd);
                }
                else if (redir->type == REDIR_APPEND)
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
                else if (redir->type == REDIR_HEREDOC)
                {
                    int herdoc = open(redir->filename, O_RDONLY);
                    if (herdoc < 0)
                    {
                        perror("open");
                        exit(1);
                    }
                    dup2(herdoc, STDIN_FILENO);
                    close(herdoc);
                    unlink(redir->filename);
                }
                redir = redir->next;
            }
        }

        if (execve(cmd_path, cmd->cmd, copier_env) == -1)
            exit(127); // Execve failed
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        int status;
        waitpid(id, &status, 0);
        int exit_code = handle_exit_status(status);
        if (exit_code == 131)
            write(1, "quit (core dumped)\n", 19);
        else if (exit_code == 130)
            write(1, "\n", 1);
        g_exit_status = exit_code;
        setup_signals();
    }
}

void built_in(t_command *cmd, t_env *env, t_gc **gc)
{
    char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int j = 0;
    int found = 0;
    int save_in = -1;
    int save_out = -1;

    if (cmd->has_redirect)
    {
        save_in = dup(STDIN_FILENO);
        save_out = dup(STDOUT_FILENO);
        if (cmd->has_redirect)
        {
            t_redirect *redir = cmd->redirects;
            while (redir)
            {
                if (redir->type == REDIR_IN)
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
                else if (redir->type == REDIR_OUT)
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
                else if (redir->type == REDIR_APPEND)
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
                else if (redir->type == REDIR_HEREDOC)
                {
                    printf("dkhel\n");
                    int herdoc = open(redir->filename, O_RDONLY);
                    if (herdoc < 0)
                    {
                        perror("open");
                        exit(1);
                    }
                    dup2(herdoc, STDIN_FILENO);
                    close(herdoc);
                    unlink(redir->filename);
                }
                redir = redir->next;
            }
        }
    }

    while (builtins[j])
    {
        if ((ft_strcmp(cmd->cmd[0], builtins[j])) == 0)
        {
            found = 1;
            if ((ft_strcmp(cmd->cmd[0], "echo") == 0)) // echo
                g_exit_status = ft_echo(cmd->cmd + 1);
            else if (ft_strcmp(cmd->cmd[0], "cd") == 0) // cd
                g_exit_status = ft_cd(cmd->cmd + 1, env, gc);
            else if ((ft_strcmp(cmd->cmd[0], "pwd")) == 0) // pwd
                g_exit_status = ft_pwd();
            else if ((ft_strcmp(cmd->cmd[0], "env")) == 0) // env
                g_exit_status = ft_env(env);
            else if ((ft_strcmp(cmd->cmd[0], "export")) == 0) // export
                ft_export(cmd->cmd + 1, &env, gc);
            else if ((ft_strcmp(cmd->cmd[0], "unset")) == 0) // unset
                g_exit_status = ft_unset(cmd->cmd + 1, &env);
            else if ((ft_strcmp(cmd->cmd[0], "exit")) == 0) // exit
                g_exit_status = ft_exit(cmd->cmd + 1, gc);
            break;
        }
        j++;
    }
    if (cmd->has_redirect)
    {
        if (save_in != -1)
        {
            dup2(save_in, STDIN_FILENO);
            close(save_in);
        }
        if (save_out != 1)
        {
            dup2(save_out, STDOUT_FILENO);
            close(save_out);
        }
    }
    if (found == 0)
    {
        write_error(cmd->cmd[0], 2);
        g_exit_status = 127; // Command not found
    }
}
