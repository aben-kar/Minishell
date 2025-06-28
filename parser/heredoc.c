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

static volatile sig_atomic_t g_heredoc_sigint = 0;

static void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_heredoc_sigint = 1;
	write(STDOUT_FILENO, "\n", 1);
	// rl_replace_line("", 0);
	// rl_redisplay();
	rl_done = 1;
}

static t_herdoc_line	*new_heredoc_node(char *line, bool quoted,
	t_gc **gc, t_env *env)
{
	t_herdoc_line	*node;

	node = gc_alloc(sizeof(t_herdoc_line), gc);
	if (!node)
		return (NULL);
	if (quoted)
		node->line = ft_strdup_gc(line, gc);
	else
		node->line = expand_word_always_expand(line, gc, env);
	node->next = NULL;
	return (node);
}

static void	append_heredoc_node(t_herdoc_line **head,
	t_herdoc_line **tail, t_herdoc_line *new_node)
{
	if (!*head)
		*head = new_node;
	else
		(*tail)->next = new_node;
	*tail = new_node;
}

static t_herdoc_line	*collect_heredoc_lines(char *delimiter, bool quoted,
	t_gc **gc, t_env *env)
{
	t_herdoc_line	*head;
	t_herdoc_line	*tail;
	t_herdoc_line	*new_node;
	char			*line;

	g_heredoc_sigint = 0;
	signal(SIGINT, handle_heredoc_sigint);

	head = NULL;
	tail = NULL;
	while (!g_heredoc_sigint)
	{
		line = readline("> ");
		if (g_heredoc_sigint || !line)
		{
			free(line);
			break ;
		}
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		new_node = new_heredoc_node(line, quoted, gc, env);
		if (!new_node)
			break ;
		append_heredoc_node(&head, &tail, new_node);
		free(line);
	}

	signal(SIGINT, handle_sigint);
	if (g_heredoc_sigint)
	{
		g_exit_status = 130;
		return (NULL);
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

char	*handle_heredoc(const char *raw_delim, t_gc **gc, t_env *env)
{
	char			*tempfile;
	char			*delimiter;
	int				fd;
	bool			quoted;
	t_herdoc_line	*lines;

	delimiter = get_delimiter(raw_delim, gc);
	if (!delimiter)
		return (NULL);
	quoted = is_quoted_delimiter(raw_delim);
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
