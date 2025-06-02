/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:17:55 by zaakrab           #+#    #+#             */
/*   Updated: 2024/11/01 21:17:57 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlen(const char *s)
{
    if (!s)  // Only check for NULL pointer
        return 0;
    
    size_t i = 0;
    while (s[i])
        i++;
    return i;
}
