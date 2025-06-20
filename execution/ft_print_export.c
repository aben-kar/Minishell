/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:13:21 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/20 14:02:47 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_line(t_env **env, t_variable *vr, t_gc **gc)
{
	t_env	*current;

	current = *env;
	if (*(current->value))
	{
		vr->eq = ft_strjoin_gc(vr->line, "=\"", gc);
		vr->val = ft_strjoin_gc(vr->eq, current->value, gc);
		vr->final = ft_strjoin_gc(vr->val, "\"", gc);
		ft_putendl_fd(vr->final, 1);
	}
	else
	{
		vr->eq = ft_strjoin_gc(vr->line, "=\"\"", gc);
		ft_putendl_fd(vr->eq, 1);
	}
}

void	print_export(t_env **env, t_gc **gc)
{
	t_env		*current;
	t_variable	vr;

	current = *env;
	while (current)
	{
		vr.line = ft_strjoin_gc("declare -x ", current->key, gc);
		if (current->value != NULL)
			print_line(&current, &vr, gc);
		else
			ft_putendl_fd(vr.line, 1);
		current = current->next;
	}
}

bool	check_key(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!(ft_isalnum(args[i]) || args[i] == '_' || args[i] == 36))
			return (false);
		i++;
	}
	return (true);
}
