/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:59:32 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/20 14:03:10 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_input_redirect(t_redirect *redir)
{
	int	in_fd;

	validate_filename(redir->filename, 1);
	in_fd = open(redir->filename, O_RDONLY);
	if (in_fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
}

void	handle_output_redirect(t_redirect *redir)
{
	int	out_fd;

	validate_filename(redir->filename, 1);
	out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}

void	handle_append_redirect(t_redirect *redir)
{
	int	append_fd;

	validate_filename(redir->filename, 1);
	append_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (append_fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(append_fd, STDOUT_FILENO);
	close(append_fd);
}

void	handle_heredoc_redirect(t_redirect *redir)
{
	int	herdoc;

	herdoc = open(redir->filename, O_RDONLY);
	if (herdoc < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(herdoc, STDIN_FILENO);
	close(herdoc);
	unlink(redir->filename);
}

void	handel_redirection_1(t_command *cmd)
{
	t_redirect	*redir;

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return ;
	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			handle_input_redirect(redir);
		else if (redir->type == REDIR_OUT)
			handle_output_redirect(redir);
		else if (redir->type == REDIR_APPEND)
			handle_append_redirect(redir);
		else if (redir->type == REDIR_HEREDOC)
			handle_heredoc_redirect(redir);
		redir = redir->next;
	}
}
