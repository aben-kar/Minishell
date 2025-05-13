/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externel_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:21:38 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/13 17:46:20 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

char **get_path(t_env *envp)
{
    char *found;
    char **split_path;
    t_env *tmp;

    tmp = envp;
    
    char **copier_env = env_to_array(tmp);
    while (*copier_env)
    {
        found = ft_strnstr(*copier_env, "PATH=", 5);
        if (found)
        {
            split_path = ft_split(found + 5, ":");
            if (!split_path)
            {
                write(2, "PATH Not Found In Environment./n", 31);
                return (NULL);
            }
            return (split_path);
        }
        copier_env++;
    }
    return (NULL);
}

// void apply_redirections(t_command *cmd)
// {
//     int fd;

//     // Handle outfile '>' or '>>'
//     if (cmd->outfile)
//     {
//         if (cmd->append == 1)
//             fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
//         else // 0
//             fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

//         // if (fd < 0)
//         // {
//         //     perror("open outfile");
//         //     exit(1);
//         // }
//         dup2(fd, STDOUT_FILENO);
//         close(fd);
//     }
// }

bool check_command(t_command *check, t_env *envp)
{
    t_env *tmp;
    tmp = envp;
    
    if (!check || !check->cmd || !check->cmd[0])
        return (false);

    char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int j = 0;

    while (builtins[j])
    {
        if ((ft_strncmp(check->cmd[0], builtins[j], ft_strlen(builtins[j]))) == 0)
            return (false);
        j++;
    }

    if ((access(check->cmd[0], F_OK | X_OK)) == 0) // ls
        return (true);

    char **directory = get_path(tmp);
    if (!directory)
        return (false);

    int i = 0;
    while (directory[i])
    {
        char *add_slash = ft_strjoin(directory[i], "/");
        char *cmd_path = ft_strjoin(add_slash, check->cmd[0]);
        if ((access(cmd_path, F_OK | X_OK)) == 0)
            return (true);
        i++;
    }

    return (false);
}


char *find_executable_path(t_command *shell, t_env *envp)
{
    if ((access(shell->cmd[0], F_OK | X_OK)) == 0) // execute direct "/bin/ls"
        return (*(shell->cmd));                    // External Commands
    char **directory = get_path(envp);
    int i = 0;
    while (directory[i])
    {
        char *add_slash = ft_strjoin(directory[i], "/");
        char *cmd_path = ft_strjoin(add_slash, shell->cmd[0]);
        if ((access(cmd_path, F_OK | X_OK)) == 0)
            return (cmd_path); // External Commands
        i++;
    }
    return (NULL);
}

void execute_command(t_command *shell, t_env *env)
{
    if (check_command(shell, env) == true) // external command
    {
        char **copier_env = env_to_array(env);
        char *cmd_path = find_executable_path(shell, env);
        int id = fork();
        if (id == 0)
        {
            // apply_redirections(shell);
            execve(cmd_path, shell->cmd, copier_env);
            exit(1);
        }

        else
            waitpid(id, NULL, 0);
    }
    
    else // Built-in
    {
        char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
        int j = 0;
        int found = 0;

        while (builtins[j])
        {
            if ((ft_strcmp(shell->cmd[0], builtins[j])) == 0)
            {
                found = 1;
                if ((ft_strcmp(shell->cmd[0], "echo") == 0)) // echo
                {
                    ft_echo(shell->cmd + 1);
                }

                else if (ft_strcmp(shell->cmd[0], "cd") == 0) // cd
                    ft_cd(shell->cmd + 1, env);
                else if ((ft_strcmp(shell->cmd[0], "pwd")) == 0) // pwd
                    ft_pwd();
                else if ((ft_strcmp(shell->cmd[0], "env")) == 0) // env
                    ft_env(env);
                else if ((ft_strcmp(shell->cmd[0], "export")) == 0) // export
                    ft_export(shell->cmd + 1, &env);
                else if ((ft_strcmp(shell->cmd[0], "unset")) == 0) // unset
                    ft_unset(shell->cmd + 1, &env);
                else if ((ft_strcmp(shell->cmd[0], "exit")) == 0) // exit
                    ft_exit(shell->cmd + 1);
                break;
            }
            j++;
        }
        if (!found)
        {
            char *error_echo = ft_strjoin(shell->cmd[0], ": command not found");
            ft_putendl_fd(error_echo, 2);
        }
    }
}