/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:44:46 by achraf            #+#    #+#             */
/*   Updated: 2025/06/18 22:51:14 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	fork_process(void)
{
	pid_t	id;

	id = fork();
	if (id < 0)
	{
		perror("fork");
		g_exit_status = 1;
		return (-1);
	}
	return (id);
}

void	setup_child_process(t_command *current, t_pipeline *vr, t_env *env, t_gc **gc)
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

void	handle_parent_process(pid_t *pids, int *i, t_pipeline *vr, t_command *current)
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

void	wait_for_all(pid_t *pids, int cmd_count)
{
	int	status;
	int	last_status;
	int	j;
	int	exit_status;

	last_status = 0;
	j = 0;
	while (j < cmd_count)
	{
		if (waitpid(pids[j], &status, 0) > 0)
		{
			exit_status = handle_exit_status(status);
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
