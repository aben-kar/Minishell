/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:00:39 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/26 18:00:40 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*generate_temp_filename(t_gc **gc)
{
	static int	counter;
	char		*num;
	char		*filename;

	counter = 0;
	num = ft_itoa_gc(counter++, gc);
	filename = ft_strjoin_gc("/tmp/.heredoc", num, gc);
	return (filename);
}

char	*handle_heredoc(const char *delimiter, t_gc **gc)
{
	char	*line;
	char	*tempfile;
	int		fd;

	tempfile = generate_temp_filename(gc);
	fd = open(tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (tempfile);
}
