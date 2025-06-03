/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:13:21 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/03 01:14:23 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_export(t_env **env, t_gc **gc)
{
    t_env *current = *env;

    while (current)
    {
        char *line = ft_strjoin_gc("declare -x ", current->key, gc);
        if (current->value != NULL)
        {
            if (*(current->value))
            {
                char *eq = ft_strjoin_gc(line, "=\"", gc);
                char *val = ft_strjoin_gc(eq, current->value, gc);
                char *final = ft_strjoin_gc(val, "\"", gc);
                ft_putendl_fd(final, 1);
            }
            else
            {
                char *eq = ft_strjoin_gc(line, "=\"\"", gc);
                ft_putendl_fd(eq, 1);
            }
        }
        else                        // without value
            ft_putendl_fd(line, 1); // IYAS
        current = current->next;
    }
}

bool check_key(char *args)
{
    int i = 0;
    while (args[i])
    {
        if (!(ft_isalnum(args[i]) || args[i] == '_' || args[i] == 36))
            return (false);
        i++;
    }
    return (true);
}