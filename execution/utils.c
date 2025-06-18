/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:12 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/18 23:24:01 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_node(t_env *env)
{
	t_env	*tmp;
	int		count;

	tmp = env;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**env_to_array(t_env *env, t_gc **gc)
{
	t_env		*tmp;
	t_to_array	vr;

	if (!env || !gc)
		return (NULL);
	tmp = env;
	vr.size = count_node(tmp);
	vr.envp = gc_alloc(sizeof(char *) * (vr.size + 1), gc);
	if (!vr.envp)
		return (NULL);
	tmp = env;
	vr.i = 0;
	while (tmp)
	{
		vr.envp[vr.i] = ft_strjoin_gc(ft_strjoin_gc(tmp->key, "=", gc), \
			tmp->value, gc);
		tmp = tmp->next;
		vr.i++;
	}
	vr.envp[vr.i] = NULL;
	return (vr.envp);
}

void	print_error_message(char *cmd, int error_code)
{
	if (!cmd)
		return ;
	ft_putstr_fd(cmd, 2);
	if (error_code == 6)
		ft_putstr_fd(": ambiguous redirect\n", 2);
	else if (error_code == 5)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (error_code == 4)
		ft_putstr_fd(": syntax error near unexpected token `)'\n", 2);
	else if (error_code == 3)
		ft_putstr_fd(": is a directory\n", 2);
	else if (error_code == 2)
		ft_putstr_fd(": command not found\n", 2);
	else if (error_code == 1)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (error_code == 0)
		ft_putstr_fd(": No such file or directory\n", 2);
}

void	set_exit_status(int error_code)
{
	if (error_code == 5)
		g_exit_status = 1;
	else if (error_code == 4)
		g_exit_status = 2;
	else if (error_code == 3)
		g_exit_status = 126;
	else if (error_code == 2)
		g_exit_status = 127;
	else if (error_code == 1)
		g_exit_status = 126;
	else if (error_code == 0)
		g_exit_status = 127;
}

void	write_error(char *cmd, int error_code)
{
	print_error_message(cmd, error_code);
	set_exit_status(error_code);
}
