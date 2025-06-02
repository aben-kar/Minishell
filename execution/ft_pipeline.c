/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:11:45 by achraf            #+#    #+#             */
/*   Updated: 2025/06/03 00:15:31 by acben-ka         ###   ########.fr       */
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
        int sig = 128 + WTERMSIG(status);
        return sig;
    }
    return 1; // Fallback
}

int count_commands(t_command *cmd)
{
    int count = 0;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return count;
}

int create_pipe_if_needed(int fd[2], t_command *current)
{
    if (current->next)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            g_exit_status = 1;
            return -1;
        }
    }
    return 0;
}

pid_t fork_process()
{
    pid_t id = fork();
    if (id < 0)
    {
        perror("fork");
        g_exit_status = 1;
        return -1;
    }
    return id;
}

void setup_child_process(t_command *current, int save_fd, int fd[2], t_env *env, t_gc **gc)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

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
        handel_redirection_1(current);

    excute_cmd_in_pipe(current, env, gc);
}

void handle_parent_process(pid_t *pids, int id, int *i, int *save_fd, int fd[2], t_command *current)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    pids[(*i)++] = id;

    if (*save_fd != -1)
        close(*save_fd);

    if (current->next)
    {
        close(fd[1]);
        *save_fd = fd[0];
    }
}

void wait_for_all(pid_t *pids, int cmd_count)
{
    int status;
    int last_status = 0;
    for (int j = 0; j < cmd_count; j++)
    {
        if (waitpid(pids[j], &status, 0) > 0)
        {
            int exit_status = handle_exit_status(status);
            if (j == cmd_count - 1)
            {
                if (exit_status == 131)
                    write(1, "quit (core dumped)\n", 19);
                else if (exit_status == 130)
                    write(1, "\n", 1);
                last_status = exit_status;
            }
        }
    }
    g_exit_status = last_status;
    setup_signals();
}

void execute_multi_pipe(t_command *cmd, t_env *env, t_gc **gc)
{
    int fd[2];
    int save_fd = -1;
    pid_t id;
    pid_t *pids;
    t_command *current = cmd;
    int cmd_count = count_commands(cmd);
    int i = 0;

    pids = gc_alloc(sizeof(pid_t) * cmd_count, gc);
    while (current)
    {
        if (create_pipe_if_needed(fd, current) == -1)
            return;

        id = fork_process();
        if (id == -1)
            return;

        if (id == 0)
            setup_child_process(current, save_fd, fd, env, gc);
        else
        {
            handle_parent_process(pids, id, &i, &save_fd, fd, current);
            current = current->next;
        }
    }
    wait_for_all(pids, cmd_count);
}

