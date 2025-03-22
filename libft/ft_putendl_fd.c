/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:21:20 by acben-ka          #+#    #+#             */
/*   Updated: 2024/11/12 15:22:01 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// int main()
// {
//     int fd = open("test", O_CREAT | O_RDWR | O_TRUNC);
//     ft_putendl_fd("pixou", fd);
//     printf("%d\n", fd);
//     usleep(10000);
//     int fd2 = open("test", O_RDWR | O_APPEND);
//     printf("%d\n", fd2);
//     return 0;
// }