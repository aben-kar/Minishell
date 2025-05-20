/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:11:45 by achraf            #+#    #+#             */
/*   Updated: 2025/05/20 23:55:36 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_multi_pipe(t_command *cmd, t_env *env, t_gc **gc)
{
    int fd[2];
    int save_fd = -1;
    int status;
    pid_t id;
    t_command *current = cmd;

    while (current)
    {
        if (current->next) // katbe9a t add l pipe tal (pipe->next == null)
        {
            if (pipe(fd) == -1)
            {
                perror("pipe");
                g_exit_status = 1;
                return;
            }
        }

        id = fork();
        if (id < 0)
        {
            perror("fork");
            g_exit_status = 1;
            return;
        }

        if (id == 0)
        {
            signal(SIGINT, SIG_DFL); // TEST
            signal(SIGQUIT, SIG_DFL); // TEST
            // dup2(tmp, STDERR_FILENO);
            if (save_fd != -1)
            {
                // printf ("halawa\n");
                dup2(save_fd, STDIN_FILENO);
                close(save_fd);
            }
            
            if (current->next)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            if (current->has_redirect)
            {
                t_redirect *redir = current->redirects;
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
            excute_cmd_in_pipe(current, env, gc);
            exit(127);
        }
        else
        {
            signal(SIGINT, SIG_IGN); // TEST
            signal(SIGQUIT, SIG_IGN); // TEST
            // printf ("dekhel hena\n");
            if (save_fd != -1)
                close(save_fd);

            if (current->next)
            {
                close(fd[1]);
                save_fd = fd[0];
            }
            current = current->next;
        }
    }
    while (waitpid(-1, &status, 0) > 0) 
    {
        if (WIFEXITED(status))
        {
            g_exit_status = WEXITSTATUS(status);
             // printf ("exit1 == %d\n", g_exit_status);
        }
        else if (WIFSIGNALED(status))
        {
            g_exit_status = 128 + WTERMSIG(status);
            // printf ("exit2 == %d\n", g_exit_status);
        }
        setup_signals();
    }
}

