/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:00:57 by achraf            #+#    #+#             */
/*   Updated: 2025/06/20 14:02:39 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	excute_cmd_in_pipe(t_command *cmds, t_env *env, t_gc **gc)
{
	char	**copier_env;
	char	*cmd_path;

	if (check_command(cmds) == false)
	{
		built_in(cmds, &env, gc);
		exit(g_exit_status);
	}
	else
	{
		copier_env = env_to_array(env, gc);
		cmd_path = find_executable_path(cmds, env, gc);
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

int	handle_exit_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		sig = 128 + WTERMSIG(status);
		return (sig);
	}
	return (1);
}

int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}
