/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reirection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:57:34 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/03 01:01:14 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int contains_space(char *str)
{
    while (*str)
    {
        if (*str == ' ')
            return 1;
        str++;
    }
    return 0;
}

int validate_filename(char *filename)
{
    if (!filename || !filename[0] || contains_space(filename))
    {
        ft_putendl_fd("ambiguous redirect", 2);
        exit(1);
    }
    return 1;
}
