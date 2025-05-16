/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:00:57 by achraf            #+#    #+#             */
/*   Updated: 2025/05/16 01:21:14 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void excute_cmd_in_pipe(t_command *cmd, t_env *env, t_gc **gc)
{
    if (check_command(cmd, env, gc) == false)
    {
        built_in(cmd, env, gc);
        exit(0);
    }
    else
    {
        char **copier_env = env_to_array(env);
        char *cmd_path = find_executable_path(cmd, env);
        // apply_redirections(cmd);
        execve(cmd_path, cmd->cmd, copier_env);
        exit(0);
    }
}
