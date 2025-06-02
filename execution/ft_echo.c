/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:20:57 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/02 16:05:27 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

int multiple_n(char *str) // katcheki mora "-n" wach kolchi "n"
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int ft_echo(char **args)
{
	int i = 0;
	int newline = 1;
	
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0 && multiple_n(args[i] + 2))
	{
		newline = 0;
		i++;
	}

	// Print args
	while (args[i])
	{	
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}

	// Print newline if needed
	if (newline)
		write(1, "\n", 1);

	return (0);
}
