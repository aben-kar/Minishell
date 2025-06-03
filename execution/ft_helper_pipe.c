/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:00:57 by achraf            #+#    #+#             */
/*   Updated: 2025/06/03 01:39:46 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void excute_cmd_in_pipe(t_command *cmds, t_env *env, t_gc **gc)
{
    if (check_command(cmds) == false)
    {
        built_in(cmds, &env, gc);
        exit(g_exit_status);
    }
    else
    {
        char **copier_env = env_to_array(env, gc);
        char *cmd_path = find_executable_path(cmds, env, gc); // lg
        if (!cmd_path)
        {
            exit(g_exit_status);
        }
        if (execve(cmd_path, cmds->cmd, copier_env) == -1)
        {
            exit(g_exit_status);
        }
    }
}

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
