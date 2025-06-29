/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:50:05 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/29 20:50:06 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	handle_heredoc_child(t_heredoc_ctx *ctx)
{
	t_herdoc_line	*lines;
	int				fd;

	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	lines = collect_heredoc_lines(ctx->delimiter,
			ctx->quoted, ctx->gc, ctx->env);
	fd = open(ctx->tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	write_heredoc_lines(fd, lines);
	close(fd);
	exit(0);
}

bool	handle_heredoc_parent(pid_t pid)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			g_exit_status = 130;
		else
			g_exit_status = 128 + sig;
		return (false);
	}
	if (WIFEXITED(status))
	{
		sig = WEXITSTATUS(status);
		if (sig != 0)
		{
			g_exit_status = sig;
			return (false);
		}
	}
	return (true);
}
