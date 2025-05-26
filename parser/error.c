/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:47:41 by zaakrab           #+#    #+#             */
/*   Updated: 2025/05/26 20:36:38 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bash_syntax_error(const char *token)
{
	if (!token)
	{
		write (2, "bash: syntax error near unexpected token `newline'\n", 51);
		return ;
	}
	write (2, "bash: syntax error near unexpected token `", 42);
	write (2, token, ft_strlen(token));
	write (2, "'\n", 2);
}

void	bash_unclosed_quote_error(char quote)
{
	write (2, "bash: unexpected EOF while looking for matching `", 48);
	write (2, &quote, 1);
	write (2, "'\n", 2);
	write (2, "bash: syntax error: unexpected end of file\n", 43);
}
