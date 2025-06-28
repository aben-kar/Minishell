/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 08:31:45 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/28 18:48:41 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static volatile sig_atomic_t g_heredoc_sigint = 0;

// static void handle_heredoc_sigint(int sig)
// {
// 	(void)sig;
// 	g_heredoc_sigint = 1;
// 	write(STDOUT_FILENO, "\n", 1);
// 	// rl_replace_line("", 0);
// 	// rl_redisplay();
// 	// rl_done = 1;
// }

static void handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_heredoc_sigint = 1;
	write(STDOUT_FILENO, "\n", 1);
}

static t_herdoc_line *new_heredoc_node(char *line, bool quoted,
									   t_gc **gc, t_env *env)
{
	t_herdoc_line *node;

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

static void append_heredoc_node(t_herdoc_line **head,
								t_herdoc_line **tail, t_herdoc_line *new_node)
{
	if (!*head)
		*head = new_node;
	else
		(*tail)->next = new_node;
	*tail = new_node;
}

static t_herdoc_line *collect_heredoc_lines(char *delimiter, bool quoted,
											t_gc **gc, t_env *env)
{
	t_herdoc_line	*head;
	t_herdoc_line	*tail;
	t_herdoc_line	*new_node;
	char			*line;

	g_heredoc_sigint = 0;
	// signal(SIGINT, handle_heredoc_sigint);

	head = NULL;
	tail = NULL;
	while (1)
	{
		line = readline("> ");
		if (g_heredoc_sigint || !line)
		{
			// free(line);
			exit(130);
			// break;
		}
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		new_node = new_heredoc_node(line, quoted, gc, env);
		if (!new_node)
			break;
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

static void write_heredoc_lines(int fd, t_herdoc_line *lines)
{
	while (lines)
	{
		write(fd, lines->line, ft_strlen(lines->line));
		write(fd, "\n", 1);
		lines = lines->next;
	}
}

char *handle_heredoc(const char *raw_delim, t_gc **gc, t_env *env)
{
	char *tempfile;
	char *delimiter;
	bool quoted;
	pid_t pid;
	int status;

	delimiter = get_delimiter(raw_delim, gc);
	if (!delimiter)
		return (NULL);
	quoted = is_quoted_delimiter(raw_delim);
	tempfile = generate_temp_filename(gc);

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	pid = fork();
	if (pid < 0)
		return (NULL);

	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_sigint);
		// signal(SIGQUIT, SIG_IGN);

		t_herdoc_line *lines = collect_heredoc_lines(delimiter, quoted, gc, env);
		if (!lines)
		{
			free (lines);
			exit(130); // SIGINT
		}
		int fd = open(tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit(1);
		write_heredoc_lines(fd, lines);
		close(fd);
		exit(0);
	}

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		int exit_code = WEXITSTATUS(status);
		if (exit_code == 130)
		{
			g_exit_status = 130;
			return (NULL);
		}
		else if (exit_code != 0)
		{
			g_exit_status = 1;
			return (NULL);
		}
	}
	else if (WIFSIGNALED(status))
	{
		g_exit_status = 130;
		return (NULL);
	}
	return (tempfile);
}
