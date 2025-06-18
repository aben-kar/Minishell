/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:11:45 by achraf            #+#    #+#             */
/*   Updated: 2025/06/18 22:49:31 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_empty_command(t_command **current)
{
	if ((*current)->has_redirect)
	{
		redir_without_cmd(*current);
		(*current) = (*current)->next;
		return ;
	}
	(*current)->cmd = (*current)->cmd + 1;
}

void	setup_pipeline(t_pipeline *pl, t_command *cmd)
{
	if (pipe(pl->fd) == -1 && cmd->next)
	{
		perror("pipe");
		exit(1);
	}
	pl->id = fork_process();
}

void	init_pipeline(t_pipeline *pl, t_command *cmd, t_gc **gc)
{
	pl->save_fd = -1;
	pl->cmd_count = count_commands(cmd);
	pl->pids = gc_alloc(sizeof(pid_t) * count_commands(cmd), gc);
}

void	process_commands(t_command *current, t_pipeline *pl, t_env *env, t_gc **gc)
{
	int	i;

	i = 0;
	while (current)
	{
		if (!current->cmd || !current->cmd[0] || !current->cmd[0][0])
		{
			handle_empty_command(&current);
			if (!current)
				break ;
			continue ;
		}
		setup_pipeline(pl, current);
		if (pl->id == -1)
			return ;
		if (pl->id == 0)
			setup_child_process(current, pl, env, gc);
		else
			handle_parent_process(pl->pids, &i, pl, current);
		current = current->next;
	}
}

void	execute_multi_cmd(t_command *cmd, t_env *env, t_gc **gc)
{
	t_command	*current;
	t_pipeline	pl;

	current = cmd;
	init_pipeline(&pl, cmd, gc);
	process_commands(current, &pl, env, gc);
	wait_for_all(pl.pids, pl.cmd_count);
}
