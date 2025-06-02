/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:31:35 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/02 16:24:05 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
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

