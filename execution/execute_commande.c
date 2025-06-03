/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commande.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:42:58 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/03 01:02:07 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_command(t_command *shell, t_env **env, t_gc **gc)
{
    if (!shell->cmd || !shell->cmd[0] || !shell->cmd[0][0] || !env | !gc)
    {
        shell->cmd = shell->cmd + 1;
        if (!shell->cmd || !shell->cmd[0] || !shell->cmd[0][0])
            return;
    }
    if (!(alpha(shell->cmd[0]) || shell->cmd[0][0] == '/') || (ft_strcmp(shell->cmd[0], "()") == 0))
    {
        if (ft_strcmp(shell->cmd[0], "()") == 0)
        {
            write_error(shell->cmd[0], 4);
            return;
        }
        write_error(shell->cmd[0], 2);
        return;
    }
    if (check_command(shell) == true) // external command
        execute_external_cmd(shell, *env, gc);

    else if (check_command(shell) == false)
        built_in(shell, env, gc);
}
