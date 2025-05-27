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

bool	is_quoted_delimiter(const char *delimiter)
{
	if (delimiter == NULL)
		return (false);
	if (delimiter[0] == '\'' || delimiter[0] == '"')
		return (true);
	return (false);
}

char	*strip_quotes(const char *str, t_gc **gc)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') ||
					 (str[0] == '"' && str[len - 1] == '"')))
		return (ft_strndup(str + 1, len - 2, gc));
	return (ft_strdup_gc(str, gc));
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
	char	*line;
	char	*expanded;
	char	*tempfile;
	char	*delimiter;
	int		fd;
	bool	quoted;

	quoted = is_quoted_delimiter(raw_delim);
	delimiter = strip_quotes(raw_delim, gc);
	tempfile = generate_temp_filename(gc);
	fd = open(tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		g_exit_status = 1;
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (!quoted)
			expanded = expand_word(line, gc, env);
		else
			expanded = ft_strdup_gc(line, gc);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (tempfile);
}
