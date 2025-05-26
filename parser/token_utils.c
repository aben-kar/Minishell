/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:48:09 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/24 20:48:10 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*add_token(t_token *last, char *value, t_gc **gc)
{
	t_token	*new;

	new = NULL;
	new = gc_alloc(sizeof(t_token), gc);
	new->value = value;
	new->next = NULL;
	if (last)
		last->next = new;
	return (new);
}

t_redirect	*add_redir(t_redirect *list, char *filename, int type, t_gc **gc)
{
	t_redirect	*new;
	t_redirect	*tmp;

    new = NULL;
    tmp = NULL;
    new = gc_alloc(sizeof(t_redirect), gc);
	new->filename = filename;
	new->type = type;
	new->next = NULL;
	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (list);
}

char    **argv_add(char **argv, const char *value, t_gc **gc)
{
	int     i;
    int     j;
	char    **new_argv;

    i = 0;
	while (argv && argv[i])
		i++;
	new_argv = gc_alloc(sizeof(char *) * (i + 2), gc);
	if (!new_argv)
		return (NULL);
    j = -1;
    while (++j < i)
		new_argv[j] = argv[j];
	new_argv[i] = ft_strdup_gc(value, gc);
	new_argv[i + 1] = NULL;
	return (new_argv);
}

t_command	*add_command(t_command *list, t_command *new)
{
    t_command *tmp;

    tmp = NULL;
	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (list);
}
