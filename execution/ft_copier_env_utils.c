/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copier_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:05:24 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/20 14:49:18 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_null(t_env **head, t_gc **gc)
{
	t_env	*tmp;
	char	*pwd;

	tmp = gc_alloc(sizeof(t_env), gc);
	if (!tmp)
		exit(1);
	pwd = getcwd(NULL, 0);
	insert_at_end(head, ft_strdup_gc("PWD", gc), ft_strdup_gc(pwd, gc), gc);
	insert_at_end(head, ft_strdup_gc("SHLVL", gc), ft_strdup_gc("1", gc), gc);
	insert_at_end(head, ft_strdup_gc("_", gc),
	ft_strdup_gc("/usr/bin/env", gc), gc);
	if (!*head)
	{
		*head = tmp;
		return ;
	}
	free(pwd);
}

void	insert_at_end(t_env **head, char *key, char *value, t_gc **gc)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = gc_alloc(sizeof(t_env), gc);
	if (!new_node)
		exit(1);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}

void	handle_shlvl_env(t_env **head, char *equal, t_gc **gc)
{
	int		shlvl;
	char	*key;
	char	*shlvl_str;
	char	*value;

	shlvl = 1;
	key = ft_strdup_gc("SHLVL", gc);
	if (*(equal + 1) != '\0')
		shlvl = ft_atoi(equal + 1) + 1;
	shlvl_str = ft_itoa(shlvl);
	value = ft_strdup_gc(shlvl_str, gc);
	free(shlvl_str);
	insert_at_end(head, key, value, gc);
}

void	handle_regular_env(t_env **head, char *envp_line,
		char *equal, t_gc **gc)
{
	int		key_len;
	char	*key;
	char	*value;

	key_len = equal - envp_line;
	key = ft_substr_gc(envp_line, 0, key_len, gc);
	value = ft_strdup_gc(equal + 1, gc);
	insert_at_end(head, key, value, gc);
}

void	process_env_line(t_env **head, char *envp_line, t_gc **gc)
{
	char	*equal;
	int		key_len;
	char	*temp_key;

	equal = ft_strchr(envp_line, '=');
	if (!equal)
		return ;
	key_len = equal - envp_line;
	temp_key = ft_substr_gc(envp_line, 0, key_len, gc);
	if (ft_strcmp(temp_key, "SHLVL") == 0)
		handle_shlvl_env(head, equal, gc);
	else
		handle_regular_env(head, envp_line, equal, gc);
}
