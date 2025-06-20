/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:57:34 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/20 14:03:05 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains_space(char *str)
{
	while (*str)
	{
		if (*str == ' ')
			return (1);
		str++;
	}
	return (0);
}

int	validate_filename(char *filename, int setup)
{
	if (setup)
	{
		if ((!filename || !filename[0] || contains_space(filename)))
		{
			write_error(filename, 6);
			exit(1);
		}
	}
	else
	{
		write_error(filename, 6);
		g_exit_status = 1;
	}
	return (1);
}

void	redir_in(t_redirect *redir)
{
	if (access(redir->filename, F_OK) == 0)
		return ;
	else
		write_error(redir->filename, 5);
	return ;
}

void	redir_out(t_redirect *redir)
{
	int	out_fd;

	out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror("open");
		exit(1);
	}
}

void	redir_append(t_redirect *redir)
{
	int	append_fd;

	append_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (append_fd < 0)
	{
		perror("open");
		exit(1);
	}
}
