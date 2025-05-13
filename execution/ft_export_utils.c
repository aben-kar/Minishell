/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:52:34 by aben-kar          #+#    #+#             */
/*   Updated: 2025/05/13 16:25:30 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

int key_with_equal(char *arg, char **key, char **value, t_env **env)
{
    t_env *tmp = *env;
    char *equal = ft_strchr(arg, '=');
    if (!equal)
    {
        ft_putendl_fd("error syntax", 1);
        return (1);
    }

    int key_len = equal - arg;
    *key = ft_substr(arg, 0, key_len);
    
    if (*(equal + 1) == '\0')
        *value = ft_strdup("");
    else
        *value = ft_strdup(equal + 1);

    // if (!*value)
    // {
    //     free(*key);
    //     return (1);
    // }

    if (check_plus(*key) == 12)
    {
        ft_putendl_fd("error plus", 1);
        // free(*key);
        // free(*value);
        return (1);
    }

    t_env *repetition = *env;
    while (repetition)
    {
        if (ft_strcmp(repetition->key, *key) == 0)
        {
            free(repetition->value);
            repetition->value = *value;
            // free(*key);
            return (0);
        }
        repetition = repetition->next;
    }
    insert_at_end(&tmp, *key, *value);
    return (0);
}

int key_with_plus(char *arg, char **key, char **value, t_env **env)
{
    t_env *tmp = *env;
    char *equal = ft_strchr(arg, '=');
    int key_len = equal - arg - 1;
    *key = ft_substr(arg, 0, key_len);
    *value = ft_strdup(equal + 1);

    if (check_plus(*key) == 12)
    {
        ft_putendl_fd("error plus", 1);
        // free(*key);
        // free(*value);
        return (1);
    }    
    
    t_env *repetition = *env;
    while (repetition)
    {
        if ((ft_strcmp(repetition->key, *key)) == 0)
        {
            if (repetition->value == NULL)
                repetition->value = ft_strdup("");
            char *new_val = ft_strjoin(repetition->value, *value);
            // free(repetition->value);
            // free(*value);
            repetition->value = new_val;
            // free(*key);
            return 0;
        }
        repetition = repetition->next;
    }
    
    // if (*value == NULL)
    //     *value = ft_strdup("");
        
    insert_at_end(&tmp, *key, *value);
    return 0;
}