/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:22:52 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/02 16:22:53 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_STRUCT_H
# define HELPER_STRUCT_H

# include "../minishell.h"

typedef struct s_env	t_env;
typedef struct s_token	t_token;
typedef struct s_gc		t_gc;

typedef struct s_expand_ctx
{
	t_gc	**gc;
	t_env	*env;
	char	**res;
}	t_expand_ctx;

typedef struct s_expctx
{
	t_gc	**gc;
	t_env	*env;
}	t_expctx;

typedef struct s_tokctx
{
	t_token	*head;
	t_token	*last;
	t_gc	**gc;
}	t_tokctx;

#endif
