/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:00:57 by achraf            #+#    #+#             */
/*   Updated: 2025/06/03 00:11:09 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void excute_cmd_in_pipe(t_command *cmds, t_env *env, t_gc **gc)
{
    if (check_command(cmds) == false)
    {
        built_in(cmds, &env, gc);
        exit(g_exit_status);
    }
    else
    {
        char **copier_env = env_to_array(env, gc);
        char *cmd_path = find_executable_path(cmds, env, gc); // lg
        if (!cmd_path)
        {
            exit(g_exit_status);
        }
        if (execve(cmd_path, cmds->cmd, copier_env) == -1)
        {
            exit(g_exit_status);
        }
    }
}
