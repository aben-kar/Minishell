/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:28:21 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/30 17:28:22 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_herdoc_line	*collect_heredoc_lines(char *delimiter, bool quoted,
											t_gc **gc, t_env *env)
{
	t_herdoc_line	*head;
	t_herdoc_line	*tail;
	t_herdoc_line	*new_node;
	char			*line;

	head = NULL;
	tail = NULL;
	while (1)
	{
		line = readline("> ");
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
	return (head);
}

void	write_heredoc_lines(int fd, t_herdoc_line *lines)
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
	t_heredoc_ctx	ctx;
	pid_t			pid;

	ctx.delimiter = get_delimiter(raw_delim, gc);
	if (!ctx.delimiter)
		return (NULL);
	ctx.quoted = is_quoted_delimiter(raw_delim);
	ctx.gc = gc;
	ctx.env = env;
	ctx.tempfile = generate_temp_filename(gc);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (NULL);
	if (pid == 0)
		handle_heredoc_child(&ctx);
	if (!handle_heredoc_parent(pid))
		return (NULL);
	return (ctx.tempfile);
}
