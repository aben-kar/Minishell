/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:31:35 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/28 22:57:44 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

int count_plus(char *arg)
{
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

int is_equal_alone(char *arg)
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

bool check_plus(char *args)
{
    int i = 0;
    while (args[i])
    {
        if (!(ft_isalnum(args[i]) || ft_isdigit(args[i]) || args[i] == '_'))
            return (false);
        i++;
    }
    return (true);
}

int handel_equal(char *args)
{
    // int i = 0;
    while (args)
    {
        if (*(args - 1) == '\0')
            return 1;
        else if (*(args + 1) == '\0')
            return 2;
        args++;
    }
    return 0;
}

int ft_export(char **args, t_env **env, t_gc **gc)
{
    if (!args[0] || !*args)
    {
        t_env *tmp = *env;
        while (tmp)
        {
            char *line = ft_strjoin_gc("declare -x ", tmp->key, gc);
            if (tmp->value != NULL)
            {
                if (*(tmp->value))
                {
                    char *eq = ft_strjoin_gc(line, "=\"", gc);
                    char *val = ft_strjoin_gc(eq, tmp->value, gc);
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
            tmp = tmp->next;
        }
    }

    
    
    t_env *tmp = *env;
    int i = 0;
    while (args[i])
    {
        if (!ft_isalpha(args[i][0]) && !(ft_isalpha(args[i][0]) && ft_isdigit(args[i][0])))
        {
            print_error(args[i], gc);
            return 1;
        }
        char *equal = ft_strchr(args[i], '='); // test+=test
        if (equal)
        {
            if (handel_equal(equal) == 1)
            {
                print_error(args[i], gc);
                return (1);
            }
            char *key = NULL;
            char *value = NULL;
            int string_len = equal - args[i] + 1;
            char *string = ft_substr_gc(args[i], 0, string_len, gc); // test=
            int check_is_equal = is_equal_alone(string);
            int exit_code;
            if (check_is_equal == 0)
            {
                exit_code = key_with_equal(args[i], &key, &value, &tmp, gc);
                return (exit_code);
            }
            else if (check_is_equal == 1)
            {
                exit_code = key_with_plus(args[i], &key, &value, &tmp, gc);
                return (exit_code);
            }
            else
            {
                print_error(args[i], gc);
                return(1);   
            }
        }
        else
        {
            char *key = args[i];
            char *value = NULL;
            insert_at_end(&tmp, key, value, gc);
        }
        i++;
    }
    return (0);
}
