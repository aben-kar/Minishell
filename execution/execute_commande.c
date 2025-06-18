/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commande.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:42:58 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/16 17:26:27 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_without_cmd(t_command *cmd)
{
	t_redirect	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			redir_in(redir);
			return ;
		}
		else if (redir->type == REDIR_OUT)
		{
			redir_out(redir);
			return ;
		}
		else if (redir->type == REDIR_APPEND)
		{
			redir_append(redir);
			return ;
		}
		redir = redir->next;
	}
}

bool	valid_cmd(t_command *cmd)
{
	if (cmd->has_redirect)
	{
		redir_without_cmd(cmd);
		return (false);
	}
	return (true);
}

int	is_cmd_alpha(t_command *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "()") == 0)
	{
		write_error(cmd->cmd[0], 4);
		return (2);
	}
	write_error(cmd->cmd[0], 2);
	return (0);
}

void	execute_command(t_command *shell, t_env **env, t_gc **gc)
{
	if (!shell->cmd || !shell->cmd[0] || !shell->cmd[0][0] || !env || !gc)
	{
		if (valid_cmd(shell) == false)
			return ;
		if (!shell->cmd || !shell->cmd[0])
			return ;
		shell->cmd = shell->cmd + 1;
		if (!shell->cmd || !shell->cmd[0] || !shell->cmd[0][0])
			return ;
	}
	if (!(alpha(shell->cmd[0]) || shell->cmd[0][0] == '/') 
		|| (ft_strcmp(shell->cmd[0], "()") == 0))
	{
		if (is_cmd_alpha(shell) == 2)
			return ;
		else
			return ;
	}
	if (check_command(shell) == true)
	{
		execute_external_cmd(shell, *env, gc);
	}
	else if (check_command(shell) == false)
		built_in(shell, env, gc);
}
