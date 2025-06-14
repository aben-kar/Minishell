/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:45:19 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/14 18:09:15 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(t_env *envp, t_gc **gc)
{
	char	*path_value;
	t_env	*tmp;
	char	**split_path;

	path_value = NULL;
	tmp = envp;
	if (!envp || !gc)
		return (NULL);
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, "PATH") == 0)
		{
			path_value = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	if (!path_value)
		return (NULL);
	split_path = ft_split_gc(path_value, ":", gc);
	if (!split_path)
		return (NULL);
	return (split_path);
}

char	*check_path_access(char **dir, char *cmd, t_gc **gc)
{
	int		i;
	char	*add_slash;
	char	*cmd_path;

	if (!dir || !cmd || !gc)
		return (NULL);
	i = 0;
	while (dir[i])
	{
		add_slash = my_strjoin(dir[i], "/", gc);
		if (!add_slash)
			return (NULL);
		cmd_path = my_strjoin(add_slash, cmd, gc);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}

char	*search_in_path_dirs(t_command *shell, t_env *envp, t_gc **gc)
{
	char	**directory;
	char	*result;

	if (!shell || !shell->cmd || !shell->cmd[0] || !envp || !gc)
		return (NULL);
	directory = get_path(envp, gc);
	if (!directory || !directory[0])
	{
		write_error(shell->cmd[0], 0);
		return (NULL);
	}
	result = check_path_access(directory, shell->cmd[0], gc);
	if (result)
		return (result);
	write_error(shell->cmd[0], 2);
	return (NULL);
}

char	*check_direct_path(t_command *shell)
{
	t_stat	info;

	// ft_memset(&info, 0, sizeof(info));
	if (stat(shell->cmd[0], &info) == 0 && S_ISDIR(info.st_mode))
	{
		write_error(shell->cmd[0], 3);
		return (NULL);
	}
	if (access(shell->cmd[0], F_OK) != 0)
	{
		write_error(shell->cmd[0], 0);
		return (NULL);
	}
	if (access(shell->cmd[0], X_OK) != 0)
	{
		write_error(shell->cmd[0], 1);
		return (NULL);
	}
	return (shell->cmd[0]);
}
