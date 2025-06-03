/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:31:35 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/03 01:39:36 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

void handle_no_equal_case(char *arg, t_env **env, t_gc **gc)
{
    t_env *tmp = *env;

    if (!first_char(arg) || !check_key(arg))
        return print_error(arg, gc);

    if (!multiple_key(tmp, arg))
    {
        char *value = NULL;
        insert_at_end(&tmp, arg, value, gc);
    }
}

void handle_equal_case(char *arg, t_env **env, t_gc **gc)
{
    t_env *tmp = *env;
    char *key = NULL;
    char *value = NULL;

    int check_equal = equal_or_plus(arg);
    if (check_equal == 0)
        key_with_equal(arg, &key, &value, &tmp, gc);
    else if (check_equal == 1)
        key_with_plus(arg, &key, &value, &tmp, gc);
    else
        print_error(arg, gc);
}

void process_single_arg(char *arg, t_env **env, t_gc **gc)
{
    if (!alpha(arg))
        return print_error(arg, gc);

    char *equal = ft_strchr(arg, '=');
    if (equal)
        handle_equal_case(arg, env, gc);
    else
        handle_no_equal_case(arg, env, gc);
}

void process_export_args(char **args, t_env **env, t_gc **gc)
{
    int i = 0;
    while (args[i])
    {
        process_single_arg(args[i], env, gc);
        i++;
    }
}

void ft_export(char **args, t_env **env, t_gc **gc)
{
    if (!args[0] || !*args)
        return print_export(env, gc);
    process_export_args(args, env, gc);
}

