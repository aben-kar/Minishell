/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:42:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/25 18:35:43 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

// int    *get_exit_status(void)
// {
//     static int    exit_status;

//     return (&exit_status);
// }

bool all_is_digit(char *arg)
{
    int i = 0;

    if (arg[i] == '+' || arg[i] == '-')
        i++;

    if (arg[i] == '\0')
    {
        printf("hena\n");
        return false;
    }

    while (arg[i])
    {
        if (!(arg[i] >= '0' && arg[i] <= '9'))
            return false;
        i++;
    }
    return true;
}

int ft_exit(char **args, t_gc **gc)
{
    // printf ("sign ==> %c\n", *args[0]);
    if (!args || !*args)
    {
        ft_putendl_fd("exit", 1);
        exit(0);
    }
    else if (!all_is_digit(args[0])) // exit: he4d: numeric argument required
    {
        ft_putendl_fd("exit", 1);
        ft_putstr_fd("exit: ", 1);
        char *join = ft_strjoin_gc(args[0], ": numeric argument required", gc);
        ft_putendl_fd(join, 1);
        exit(2);
    }
    else if (args[1]) // exit: too many arguments
    {
        ft_putendl_fd("exit", 1);
        ft_putstr_fd("exit: ", 1);
        ft_putendl_fd("too many arguments", 1);
    }
    else if (*args)
    {
        long long nbr = ft_aatoi(*args);
        if (nbr == 11)
        {
            ft_putendl_fd("exit", 1);
            ft_putstr_fd("exit: ", 1);
            char *join = ft_strjoin_gc(args[0], ": numeric argument required", gc);
            ft_putendl_fd(join, 1);
            exit(2);
        }
        ft_putendl_fd("exit", 1);
        exit(nbr);
    }
    return (0);
}
