/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:21:38 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/14 18:03:04 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

void	setup_child_process_1(t_command *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->has_redirect)
		handel_redirection_1(cmd);
}

char	*find_executable_path(t_command *shell, t_env *envp, t_gc **gc)
{
	if (ft_strchr(shell->cmd[0], '/'))
		return (check_direct_path(shell));
	return (search_in_path_dirs(shell, envp, gc));
}

void	handle_parent_process_1(int child_pid)
{
	int	status;
	int	exit_code;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(child_pid, &status, 0);
	exit_code = handle_exit_status(status);
	if (exit_code == 131)
		write(1, "quit (core dumped)\n", 19);
	else if (exit_code == 130)
		write(1, "\n", 1);
	g_exit_status = exit_code;
	setup_signals();
}

void	execute_child_process(t_command *cmd, char **copier_env, char *cmd_path)
{
	setup_child_process_1(cmd);
	if (execve(cmd_path, cmd->cmd, copier_env) == -1)
		exit(127);
}

void	execute_external_cmd(t_command *cmd, t_env *env, t_gc **gc)
{
	char	**copier_env;
	char	*cmd_path;
	int		id;

	copier_env = env_to_array(env, gc);
	cmd_path = find_executable_path(cmd, env, gc);
	if (!cmd_path)
		return ;
	id = fork();
	if (id == 0)
		execute_child_process(cmd, copier_env, cmd_path);
	else
		handle_parent_process_1(id);
}
