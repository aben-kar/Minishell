/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:11:45 by achraf            #+#    #+#             */
/*   Updated: 2025/05/19 17:30:55 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_multi_pipe(t_command *cmd, t_env *env, t_gc **gc)
{
    int fd[2];
    int save_fd = -1;
    pid_t id;
    t_command *current = cmd;


    // int tmp = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0664);
    

    

    while (current)
    {
        if (current->next) // katbe9a t add l pipe tal (pipe->next == null)
        {
            if (pipe(fd) == -1)
            {
                perror("pipe");
                return;
            }
        }

        id = fork();
        if (id < 0)
        {
            perror("fork");
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
                            exit(EXIT_FAILURE);
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
                            exit(EXIT_FAILURE);
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
                            exit(EXIT_FAILURE);
                        }
                        dup2(append_fd, STDOUT_FILENO);
                        close(append_fd);
                    }
                    redir = redir->next;
                }
            }
            excute_cmd_in_pipe(current, env, gc);
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
    while (waitpid(-1, NULL, 0) > 0); // DYALK
    // int status;
    // while (waitpid(-1, &status, 0) > 0)
    // {
    //     if (status == 2 << 8)
    //         write(1, "\n", 1);
    // }
    setup_signals(); // TEST
    // ktb ach endlk f tmp (stderr_)
    // unlink("tmp");
}

