/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:11:45 by achraf            #+#    #+#             */
/*   Updated: 2025/05/30 04:09:15 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_exit_status(int status)
{
    if (WIFEXITED(status))
    {
        // Child exited normally - return its exit code
        return WEXITSTATUS(status);
    }
    else if (WIFSIGNALED(status))
    {
        // Child was killed by signal - return 128 + signal number
        int sig = WTERMSIG(status);
        return 128 + sig;
    }
    return 1; // Fallback
}

void execute_multi_pipe(t_command *cmd, t_env *env, t_gc **gc)
{
    int fd[2];
    int save_fd = -1;
    int status;
    pid_t id;
    pid_t *pids = NULL;
    t_command *current = cmd;
    int cmd_count = 0;
    int i = 0;

    t_command *temp = cmd;
    while (temp)
    {
        cmd_count++;
        temp = temp->next;
    }
    
    pids = gc_alloc(sizeof(pid_t) * cmd_count, gc);
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
            signal(SIGINT, SIG_DFL);  // TEST
            signal(SIGQUIT, SIG_DFL); // TEST
            if (save_fd != -1)
            {
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
            excute_cmd_in_pipe(current, env, gc);
            // exit(127);
        }
        else
        {
            signal(SIGINT, SIG_IGN);  // TEST
            signal(SIGQUIT, SIG_IGN); // TEST
            
            pids[i++] = id;
            
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
    int last_status = 0;
    int j = 0;
    while (j < cmd_count)
    {
        if ((waitpid(pids[j], &status, 0)) > 0)
        {
            int exit_status = handle_exit_status(status);
            
            if (j == cmd_count - 1)
            {
                if (exit_status == 131)
                    write(1, "quit (core dumped)\n", 19);
                else if (exit_status == 130)
                    write(1, "\n", 1);
                last_status = exit_status; // nsetiw last status
                
            }
        }
        j++;
    }
    g_exit_status = last_status; // nsetiw g_exit_status b last status
    setup_signals();
}
