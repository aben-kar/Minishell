/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:52:34 by aben-kar          #+#    #+#             */
/*   Updated: 2025/05/25 18:30:37 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_error(char *key, t_gc **gc)
{
    char *error_1 = ft_strjoin_gc("export: ", key, gc);
    char *error_2 = ft_strjoin_gc(error_1, ": not a valid identifier", gc);
    ft_putendl_fd(error_2, 1);
}

bool check_key(char *key)
{
    int i = 0;
    if ((key[i] >= '0' && key[i] <= '9') || key[i] == 61)
        return (false);
    return(true);
}

int key_with_equal(char *arg, char **key, char **value, t_env **env, t_gc **gc)
{
    t_env *tmp = *env;
    char *equal = ft_strchr(arg, '=');

    int key_len = equal - arg;
    *key = ft_substr_gc(arg, 0, key_len, gc);
    if (check_key(*key) == false)
    {
        print_error(*key, gc);
        return(1);
    }
    
    if (*(equal + 1) == '\0') // ==> test=
        *value = ft_strdup_gc("", gc);
    else
        *value = ft_strdup_gc(equal + 1, gc);
    if (check_plus(*key) == false)
    {
        print_error(*key, gc);
        return (1);
    }
    t_env *repetition = *env;
    while (repetition)
    {
        if (ft_strcmp(repetition->key, *key) == 0)
        {
            repetition->value = *value;
            return (0);
        }
        repetition = repetition->next;
    }
    insert_at_end(&tmp, *key, *value, gc);
    return (0);
}

int key_with_plus(char *arg, char **key, char **value, t_env **env, t_gc **gc)
{
    t_env *tmp = *env;
    char *equal = ft_strchr(arg, '=');
    int key_len = equal - arg - 1;
    *key = ft_substr_gc(arg, 0, key_len, gc);
    *value = ft_strdup_gc(equal + 1, gc);
    
    if (check_key(*key) == false)
    {
        print_error(*key, gc);
        return(1);
    }
    
    if (check_plus(*key) == false)
    {
        print_error(*key, gc);
        return (1);
    }    
    
    t_env *repetition = *env;
    while (repetition)
    {
        if ((ft_strcmp(repetition->key, *key)) == 0)
        {
            if (repetition->value == NULL)
                repetition->value = ft_strdup_gc("", gc);
            char *new_val = ft_strjoin_gc(repetition->value, *value, gc);
            repetition->value = new_val;
            return (0);
        }
        repetition = repetition->next;
    }
    insert_at_end(&tmp, *key, *value, gc);
    return 0;
}