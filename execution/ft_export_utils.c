/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:52:34 by aben-kar          #+#    #+#             */
/*   Updated: 2025/06/02 16:10:43 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

bool first_char(char *key)
{
    int i = 0;
    if ((key[i] >= '0' && key[i] <= '9') || key[i] == 61)
        return (false);
    return(true);
}

char *implement_key(char *args, t_gc **gc)
{
    char *key;
    int is_equal = equal_or_plus(args);
    char *equal = ft_strchr(args, '=');
    int position_equal;
    if (is_equal == 0)
    {
        position_equal = equal - args;
        key = ft_substr_gc(args, 0, position_equal, gc);
    }
    else
    {
        position_equal = equal - args - 1;
        key = ft_substr_gc(args, 0, position_equal, gc);
    }
    return (key);
    
}
char *implement_value(char *args, t_gc **gc)
{
    char *value;
    char *equal = ft_strchr(args, '=');
    if (*(equal + 1) == '\0')
        value = ft_strdup_gc("", gc);
    else
        value = ft_strdup_gc(equal + 1, gc);
    return (value);
}

void key_with_equal(char *arg, char **key, char **value, t_env **env, t_gc **gc)
{
    t_env *tmp = *env;
    *key = implement_key(arg, gc);
    if ((first_char(*key) == false) || (check_key(*key) == false))
    {
        print_error(*key, gc);
        return ;
    }
    *value = implement_value(arg, gc);
    t_env *repetition = *env;
    while (repetition)
    {
        if (ft_strcmp(repetition->key, *key) == 0)
        {
            repetition->value = *value;
            return ;
        }
        repetition = repetition->next;
    }
    insert_at_end(&tmp, *key, *value, gc);
}

void key_with_plus(char *arg, char **key, char **value, t_env **env, t_gc **gc)
{
    t_env *tmp = *env;
    *key = implement_key(arg, gc);
    if ((first_char(*key) == false) || (check_key(*key) == false))
    {
        print_error(*key, gc);
        return ;
    }
    *value = implement_value(arg, gc);
    
    t_env *repetition = *env;
    while (repetition)
    {
        if ((ft_strcmp(repetition->key, *key)) == 0)
        {
            char *new_val = ft_strjoin_gc(repetition->value, *value, gc);
            repetition->value = new_val;
            return ;
        }
        repetition = repetition->next;
    }
    insert_at_end(&tmp, *key, *value, gc);
}
