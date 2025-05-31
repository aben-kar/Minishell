/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 08:31:45 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/31 08:31:46 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_herdoc_line	*collect_heredoc_lines(char *delimiter, bool quoted,
	t_gc **gc, t_env *env)
{
	t_herdoc_line	*head;
	t_herdoc_line	*tail;
	t_herdoc_line	*new_node;
	char			*line;
	char			*expanded;

	head = NULL;
	tail = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		new_node = gc_alloc(sizeof(t_herdoc_line), gc);
		if (!new_node)
			break ;
		if (quoted)
			expanded = ft_strdup_gc(line, gc);
		else
			expanded = expand_word_always_expand(line, gc, env);
		new_node->line = expanded;
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		free(line);
	}
	return (head);
}

static void	write_heredoc_lines(int fd, t_herdoc_line *lines)
{
	while (lines)
	{
		write(fd, lines->line, ft_strlen(lines->line));
		write(fd, "\n", 1);
		lines = lines->next;
	}
}

char	*generate_temp_filename(t_gc **gc)
{
	static int	counter;
	char		*num;
	char		*filename;

	num = NULL;
	filename = NULL;
	counter = counter + 1;
	num = ft_itoa_gc(counter, gc);
	filename = ft_strjoin_gc("/tmp/.heredoc", num, gc);
	return (filename);
}

char	*handle_heredoc(const char *raw_delim, t_gc **gc, t_env *env)
{
	char			*tempfile;
	char			*delimiter;
	int				fd;
	bool			quoted;
	t_herdoc_line	*lines;

	quoted = is_quoted_delimiter(raw_delim);
	delimiter = strip_quotes(raw_delim, gc);
	lines = collect_heredoc_lines(delimiter, quoted, gc, env);
	tempfile = generate_temp_filename(gc);
	fd = open(tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		unlink(tempfile);
		g_exit_status = -1;
		return (NULL);
	}
	write_heredoc_lines(fd, lines);
	close(fd);
	return (tempfile);
}
