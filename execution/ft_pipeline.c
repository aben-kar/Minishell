/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:11:45 by achraf            #+#    #+#             */
/*   Updated: 2025/06/14 20:36:50 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void setup_child_process(t_command *current, t_pipeline *vr, t_env *env, t_gc **gc)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    if (vr->save_fd != -1)
    {
        dup2(vr->save_fd, STDIN_FILENO);
        close(vr->save_fd);
    }

    if (current->next)
    {
        close(vr->fd[0]);
        dup2(vr->fd[1], STDOUT_FILENO);
        close(vr->fd[1]);
    }

    if (current->has_redirect)
        handel_redirection_1(current);

    excute_cmd_in_pipe(current, env, gc);
}

void handle_parent_process(pid_t *pids, int *i, t_pipeline *vr, t_command *current)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    pids[(*i)++] = vr->id;

    if (vr->save_fd != -1)
        close(vr->save_fd);

    if (current->next)
    {
        close(vr->fd[1]);
        vr->save_fd = vr->fd[0];
    }
}

void wait_for_all(pid_t *pids, int cmd_count)
{
    int status;
    int last_status = 0;
    int j;

    j = 0;
    while (j < cmd_count)
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
        j++;
    }
    g_exit_status = last_status;
    setup_signals();
}

void execute_multi_cmd(t_command *cmd, t_env *env, t_gc **gc)
{
    t_pipeline vr;
    vr.save_fd = -1;
    pid_t *pids;
    t_command *current = cmd;
    int cmd_count = count_commands(cmd);
    int i = 0;

    pids = gc_alloc(sizeof(pid_t) * cmd_count, gc);
    while (current)
    {
        if (!current->cmd || !current->cmd[0] || !current->cmd[0][0])
        {
            if (current->has_redirect)
            {
                redir_without_cmd(current);
                current = current->next;
                continue;
            }
            current->cmd = current->cmd + 1;
        }
        if (pipe(vr.fd) == -1 && current->next)
        {
            perror("pipe");
            return;
        }
        vr.id = fork_process();
        if (vr.id == -1)
            return;

        if (vr.id == 0)
            setup_child_process(current, &vr, env, gc);
        else
        {
            handle_parent_process(pids, &i, &vr, current);
            current = current->next;
        }
    }
    wait_for_all(pids, cmd_count);
}
