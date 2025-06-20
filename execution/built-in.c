/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:42:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/20 12:46:44 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_command(t_command *cmd)
{
	int		i;
	char	**built_in;

	if (!cmd || !cmd->cmd || !cmd->cmd[0] || !cmd->cmd[0][0])
		return (false);
	i = 0;
	built_in = (char *[]){"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};
	while (built_in[i])
	{
		if (ft_strncmp(cmd->cmd[0], built_in[i], ft_strlen(built_in[i])) == 0)
			return (false);
		i++;
	}
	return (true);
}

void	handle_builtin_redirection(t_command *cmd, int *save_in, int *save_out,
		int setup)
{
	if (setup)
	{
		*save_in = dup(STDIN_FILENO);
		*save_out = dup(STDOUT_FILENO);
		handel_redirection_1(cmd);
	}
	else
	{
		if (*save_in != -1)
		{
			dup2(*save_in, STDIN_FILENO);
			close(*save_in);
		}
		if (*save_out != -1)
		{
			dup2(*save_out, STDOUT_FILENO);
			close(*save_out);
		}
	}
}

int	is_builtin_and_execute(t_command *cmd, t_env **env, t_gc **gc)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (ft_echo(cmd->cmd + 1));
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (ft_cd(cmd->cmd + 1, *env, gc));
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (ft_env(*env));
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (ft_export(cmd->cmd + 1, env, gc), g_exit_status);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(cmd->cmd + 1, env));
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (ft_exit(cmd->cmd + 1, gc));
	return (-1);
}

int	execute_builtin_command(t_command *cmd, t_env **env, t_gc **gc)
{
	t_variable	var;
	int			res;

	if (!cmd || !cmd->cmd || !cmd->cmd[0] || !env)
		return (0);
	var.built_in = (char *[]){"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};
	var.j = -1;
	while (var.built_in[++var.j])
	{
		if ((ft_strcmp(cmd->cmd[0], var.built_in[var.j])) == 0)
		{
			res = is_builtin_and_execute(cmd, env, gc);
			if (res != -1)
				return (res);
		}
	}
	write_error(cmd->cmd[0], 2);
	return (127);
}

void	built_in(t_command *cmd, t_env **env, t_gc **gc)
{
	int	save_in;
	int	save_out;

	save_in = -1;
	save_out = -1;
	if (cmd->has_redirect)
		handle_builtin_redirection(cmd, &save_in, &save_out, 1);
	g_exit_status = execute_builtin_command(cmd, env, gc);
	if (cmd->has_redirect)
		handle_builtin_redirection(cmd, &save_in, &save_out, 0);
}
