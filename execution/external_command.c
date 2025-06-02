/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:21:38 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/03 00:13:06 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

char **get_path(t_env *envp, t_gc **gc)
{
    char *path_value = NULL;
    t_env *tmp = envp;

    if (!envp || !gc)
        return NULL;

    while (tmp)
    {
        if (tmp->key && ft_strcmp(tmp->key, "PATH") == 0)
        {
            path_value = tmp->value;
            break;
        }
        tmp = tmp->next;
    }

    if (!path_value)
        return NULL;

    char **split_path = ft_split_gc(path_value, ":", gc);
    if (!split_path)
        return NULL;
    return split_path;
}

char *check_path_access(char *dir, char *cmd, t_gc **gc)
{
    if (!dir || !cmd || !gc)
        return NULL;

    while (*dir)
    {
        char *add_slash = ft_strjoin_gc(dir, "/", gc);
        if (!add_slash)
            return NULL;
        char *cmd_path = ft_strjoin_gc(add_slash, cmd, gc);
        if (!cmd_path)
            return NULL;
        if (access(cmd_path, F_OK) == 0)
        {
            if (access(cmd_path, X_OK) == 0)
                return cmd_path;
            else
            {
                write_error(cmd, 1);
                return NULL;
            }
        }
        dir++;
    }
    return NULL;
}

char *search_in_path_dirs(t_command *shell, t_env *envp, t_gc **gc)
{
    if (!shell || !shell->cmd || !shell->cmd[0] || !envp || !gc)
        return NULL;
    char **directory = get_path(envp, gc);
    if (!directory || !*directory)
    {
        write_error(shell->cmd[0], 0);
        return NULL;
    }

    if (!shell->cmd || !shell->cmd[0] || !shell->cmd[0][0])
        return NULL;
    int i = 0;
    while (directory[i])
    {
        char *result = check_path_access(directory[i], shell->cmd[0], gc);
        if (result)
            return result;
        else if (result == NULL)
            return write_error(shell->cmd[0], 2), NULL;
        i++;
    }
    return NULL;
}

char *check_direct_path(t_command *shell)
{
    t_stat info;
    ft_memset(&info, 0, sizeof(info));

    if (stat(shell->cmd[0], &info) == 0 && S_ISDIR(info.st_mode))
    {
        write_error(shell->cmd[0], 3); // Is a directory
        return NULL;
    }

    if (access(shell->cmd[0], F_OK) != 0)
    {
        write_error(shell->cmd[0], 0); // No such file
        return NULL;
    }

    if (access(shell->cmd[0], X_OK) != 0)
    {
        write_error(shell->cmd[0], 1); // Permission denied
        return NULL;
    }

    return shell->cmd[0];
}

char *find_executable_path(t_command *shell, t_env *envp, t_gc **gc)
{
    if (ft_strchr(shell->cmd[0], '/'))
        return check_direct_path(shell);
    return search_in_path_dirs(shell, envp, gc);
}

bool check_command(t_command *cmd)
{
    if (!cmd || !cmd->cmd || !cmd->cmd[0])
        return false;
    int i = 0;

    char *built_in[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

    while (built_in[i])
    {
        if ((ft_strncmp(cmd->cmd[0], built_in[i], ft_strlen(built_in[i]))) == 0)
            return (false);
        i++;
    }
    return (true);
}

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
