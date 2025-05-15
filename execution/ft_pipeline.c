/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:11:45 by achraf            #+#    #+#             */
/*   Updated: 2025/05/16 00:00:53 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_multi_pipe(t_command *cmd, t_env *env)
{
    int fd[2];
    int save_fd = -1;
    pid_t id;
    t_command *current = cmd;

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

            excute_cmd_in_pipe(current, env);
        }
        else
        {
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
    while (waitpid(-1, NULL, 0) > 0);
}