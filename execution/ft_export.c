/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:31:35 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/13 16:25:34 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

int count_plus(char *arg)
{
    char *equal = ft_strchr(arg, '=');
    int plus_count = 0;

    // Check only in the key (before '=')
    int i = 0;
    while (arg[i] && &arg[i] < equal)
    {
        if (arg[i] == '+')
            plus_count++;
        i++;
    }

    return plus_count;
}

int is_equal_alone(char *arg)
{
    char *equal = ft_strchr(arg, '=');
    // if (!equal || equal == arg) // ma kaynach = or it's the first char
    //     return false;

    if (*(equal - 1) == '+')
    {
        if (count_plus(arg) > 1)
            return 13;
        return 12; // valid KEY+=value
    }

    return 11; // '=' kayna
}

int check_plus(char *args)
{
    int i = 0;
    while (args[i])
    {
        int len = ft_strlen(args) - 1;
        if (args[len] == '+')
        {
            return 11;
            break;
        }
        else if (!((args[i] >= 65 && args[i] <= 90) || (args[i] >= 97 && args[i] <= 122) || (args[i] >= 48 && args[i] <= 57) || (args[i] == 95)))
        {
            return 12;
            break;
        }
        i++;
    }
    return 99;
}

int ft_export(char **args, t_env **env)
{
    if (!args[0] || !*args)
    {
        t_env *tmp = *env;
        int sorted = 0;
        while (!sorted)
        {
            sorted = 1;
            t_env *current = *env;
            while (current && current->next)
            {
                if (ft_strcmp(current->key, current->next->key) > 0) // ilyas+=allo
                {
                    char *temp_key = current->key;
                    current->key = current->next->key;
                    current->next->key = temp_key;

                    char *temp_value = current->value;
                    current->value = current->next->value;
                    current->next->value = temp_value;

                    sorted = 0;
                }
                current = current->next;
            }
        }

        tmp = *env;
        while (tmp)
        {
            char *line = ft_strjoin("declare -x ", tmp->key);
            if (tmp->value != NULL)
            {
                if (*(tmp->value))
                {
                    char *eq = ft_strjoin(line, "=\"");
                    char *val = ft_strjoin(eq, tmp->value);
                    char *final = ft_strjoin(val, "\"");
                    ft_putendl_fd(final, 1);
                }
                else
                {
                    char *eq = ft_strjoin(line, "=\"\""); // export ILYAS=
                    ft_putendl_fd(eq, 1);
                    free(eq);
                }
            }
            else
                ft_putendl_fd(line, 1); // IYAS
            tmp = tmp->next;
        }
    }

    else
    {
        t_env *tmp = *env;
        int i = 0;
        if ((args[i][0] >= '0' && args[i][0] <= '9') || args[i][0] == 61)
        {
            char *error_1 = ft_strjoin("export: ", *args);
            char *error_2 = ft_strjoin(error_1, ": not a valid identifier");
            ft_putendl_fd(error_2, 1);
            return (1);
        }

        while (args[i])
        {
            char *equal = ft_strchr(args[i], '=');

            if (equal)
            {
                char *key = NULL;
                char *value = NULL;
                int string_len = equal - *args + 1;
                char *string = ft_substr(*args, 0, string_len);
                int check_is_equal = is_equal_alone(string);

                if (check_is_equal == 11)
                    key_with_equal(*args, &key, &value, &tmp);
                else if (check_is_equal == 12)
                    key_with_plus(*args, &key, &value, &tmp);
                else
                    ft_putendl_fd("error > 1 plus", 1);
            }
            else
            {
                t_env *new_node = *env;
                
                char *key = args[0];
                char *value = NULL;
                
                insert_at_end(&new_node, key, value);
            }
            i++;
        }
    }
    return (0);
}
