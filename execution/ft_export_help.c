/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:08:15 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/03 01:09:14 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int alpha(char *args)
{
    int i = 0;
    while (args[i])
    {
        if ((args[i] >= 'a' && args[i] <= 'z') || (args[i] >= 'A' && args[i] <= 'Z'))
            return (1);
        i++;
    }
    return (0);
}

void print_error(char *key, t_gc **gc)
{
    char *error_1 = ft_strjoin_gc("export: ", key, gc);
    char *error_2 = ft_strjoin_gc(error_1, ": not a valid identifier", gc);
    ft_putendl_fd(error_2, 1);
    g_exit_status = 1;
}

int count_plus(char *arg)
{
    if (!arg || !arg[0])
        return 0;
    char *equal = ft_strchr(arg, '=');
    int plus_count = 0;

    int i = 0;
    while (arg[i] && (&arg[i]) < equal)
    {
        if (arg[i] == '+')
            plus_count++;
        i++;
    }

    return (plus_count);
}

int equal_or_plus(char *arg)
{
    char *equal = ft_strchr(arg, '=');
    if (*(equal - 1) == '+')
    {
        if (count_plus(arg) > 1)
            return 2;
        return 1; // valid KEY+=value
    }
    return 0; // '=' kayna
}
bool multiple_key(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return true;
        env = env->next;
    }
    return (false);
}