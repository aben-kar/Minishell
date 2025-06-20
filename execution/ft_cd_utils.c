/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:03:11 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/20 14:30:28 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*print_home(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_pwd_oldpwd(char *oldpwd, t_env **env, t_gc **gc)
{
	t_env	*current;
	char	*newpwd;

	current = *env;
	newpwd = getcwd(NULL, 0);
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			current->value = ft_strdup_gc(oldpwd, gc);
			break ;
		}
		current = current->next;
	}
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			current->value = ft_strdup_gc(newpwd, gc);
			break ;
		}
		current = current->next;
	}
	free(newpwd);
}

int	handle_home_cd(t_env *env)
{
	char	*to_home;

	to_home = print_home(env);
	if (!to_home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	if (chdir(to_home) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	validate_path(char *path)
{
	t_stat	info;

	if (stat(path, &info) != 0)
	{
		ft_putendl_fd("cd: No such file or directory", 1);
		return (1);
	}
	if (!S_ISDIR(info.st_mode))
	{
		ft_putendl_fd("cd: Not a directory", 1);
		return (1);
	}
	return (0);
}

int	change_directory(char *path, t_env **env, t_gc **gc)
{
	char	*oldpwd;
	char	*new_pwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		ft_putendl_fd("cd: Permission denied", 1);
		free(oldpwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd || !oldpwd)
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd:"
			"cannot access parent directories: No such file or directory", 1);
		free(oldpwd);
		free(new_pwd);
		return (1);
	}
	update_pwd_oldpwd(oldpwd, env, gc);
	free(new_pwd);
	free(oldpwd);
	return (0);
}
