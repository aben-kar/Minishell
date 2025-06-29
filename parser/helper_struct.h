/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:22:52 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/02 22:20:19 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_STRUCT_H
# define HELPER_STRUCT_H

# include "../minishell.h"

typedef struct s_env	t_env;
typedef struct s_token	t_token;
typedef struct s_gc		t_gc;

typedef struct s_expand_helper
{
	t_gc	**gc;
	t_env	*env;
	char	**res;
}	t_expand_helper;

typedef struct s_minus_param
{
	t_gc	**gc;
	t_env	*env;
}	t_minus_param;

typedef struct s_token_helper
{
	t_token	*head;
	t_token	*last;
	t_gc	**gc;
}	t_token_helper;

typedef struct s_heredoc_ctx
{
	char		*delimiter;
	bool		quoted;
	t_gc		**gc;
	t_env		*env;
	char		*tempfile;
}	t_heredoc_ctx;

#endif
