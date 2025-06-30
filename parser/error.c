/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:28:05 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/30 17:28:06 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bash_syntax_error(const char *token)
{
	if (!token)
		ft_putstr_fd("newline: syntax error near unexpected"
			" token `newline'\n", 2);
	else if (ft_strcmp(token, "|") == 0)
		ft_putstr_fd("|: syntax error near unexpected token `|'\n", 2);
	else if (is_redir(token))
	{
		ft_putstr_fd(token, 2);
		ft_putstr_fd(": syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
		ft_putstr_fd("bash: syntax error\n", 2);
	g_exit_status = 2;
}

void	bash_unclosed_quote_error(char quote)
{
	ft_putchar_fd(quote, 2);
	ft_putstr_fd(": unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
	ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
	g_exit_status = 2;
}
