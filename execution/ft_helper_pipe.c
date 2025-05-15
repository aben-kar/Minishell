/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:00:57 by achraf            #+#    #+#             */
/*   Updated: 2025/05/15 23:35:08 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void excute_cmd_in_pipe(t_command *cmd, t_env *env)
{
    if (check_command(cmd, env) == false)
    {
        built_in(cmd, env);
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
