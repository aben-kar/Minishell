/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:26:01 by achraf            #+#    #+#             */
/*   Updated: 2025/06/02 16:27:17 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int contains_space(char *str)
{
    while (*str)
    {
        if (*str == ' ')
            return 1;
        str++;
    }
    return 0;
}

int validate_filename(char *filename)
{
    if (!filename || !filename[0] || contains_space(filename))
    {
        ft_putendl_fd("ambiguous redirect", 2);
        exit(1);
    }
    return 1;
}

void handle_input_redirect(t_redirect *redir)
{
    validate_filename(redir->filename);
    
    int in_fd = open(redir->filename, O_RDONLY);
    if (in_fd < 0)
    {
        perror("open");
        exit(1);
    }
    dup2(in_fd, STDIN_FILENO);
    close(in_fd);
}

void handle_output_redirect(t_redirect *redir)
{
    validate_filename(redir->filename);
    
    int out_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd < 0)
    {
        perror("open");
        exit(1);
    }
    dup2(out_fd, STDOUT_FILENO);
    close(out_fd);
}

void handle_append_redirect(t_redirect *redir)
{
    validate_filename(redir->filename);
    
    int append_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (append_fd < 0)
    {
        perror("open");
        exit(1);
    }
    dup2(append_fd, STDOUT_FILENO);
    close(append_fd);
}

void handle_heredoc_redirect(t_redirect *redir)
{
    printf("dkhel\n");
    int herdoc = open(redir->filename, O_RDONLY);
    if (herdoc < 0)
    {
        perror("open");
        exit(1);
    }
    dup2(herdoc, STDIN_FILENO);
    close(herdoc);
    unlink(redir->filename);
}

void handel_redirection(t_command *cmd)
{
    t_redirect *redir = cmd->redirects;
    
    while (redir)
    {
        if (redir->type == REDIR_IN)
            handle_input_redirect(redir);
        else if (redir->type == REDIR_OUT)
            handle_output_redirect(redir);
        else if (redir->type == REDIR_APPEND)
            handle_append_redirect(redir);
        else if (redir->type == REDIR_HEREDOC)
            handle_heredoc_redirect(redir);
            
        redir = redir->next;
    }
}

void setup_child_process_1(t_command *cmd)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (cmd->has_redirect)
        handel_redirection(cmd);
}

void execute_child_process(t_command *cmd, char **copier_env, char *cmd_path)
{
    setup_child_process_1(cmd);
    if (execve(cmd_path, cmd->cmd, copier_env) == -1)
        exit(127); // Execve failed
}

void handle_parent_process_1(int child_pid)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    int status;
    waitpid(child_pid, &status, 0);
    int exit_code = handle_exit_status(status);
    
    if (exit_code == 131)
        write(1, "quit (core dumped)\n", 19);
    else if (exit_code == 130)
        write(1, "\n", 1);
    
    g_exit_status = exit_code;
    setup_signals();
}

void execute_external_cmd(t_command *cmd, t_env *env, t_gc **gc)
{
    char **copier_env = env_to_array(env, gc);
    char *cmd_path = find_executable_path(cmd, env, gc);
    
    if (!cmd_path)
        return;

    int id = fork();
    if (id == 0)
        execute_child_process(cmd, copier_env, cmd_path);
    else
        handle_parent_process_1(id);
}

void handle_builtin_redirection(t_command *cmd, int *save_in, int *save_out, int setup)
{
    if (setup)
    {
        *save_in = dup(STDIN_FILENO);
        *save_out = dup(STDOUT_FILENO);
        handel_redirection(cmd);
    }
    else
    {
        if (*save_in != -1)
        {
            dup2(*save_in, STDIN_FILENO);
            close(*save_in);
        }
        if (*save_out != -1)
        {
            dup2(*save_out, STDOUT_FILENO);
            close(*save_out);
        }
    }
}

int execute_builtin_command(t_command *cmd, t_env *env, t_gc **gc)
{
    char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int j = -1;

    while (builtins[++j])
    {
        if ((ft_strcmp(cmd->cmd[0], builtins[j])) == 0)
        {
            if ((ft_strcmp(cmd->cmd[0], "echo") == 0))
                return ft_echo(cmd->cmd + 1);
            else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
                return ft_cd(cmd->cmd + 1, env, gc);
            else if ((ft_strcmp(cmd->cmd[0], "pwd")) == 0)
                return ft_pwd();
            else if ((ft_strcmp(cmd->cmd[0], "env")) == 0)
                return ft_env(env);
            else if ((ft_strcmp(cmd->cmd[0], "export")) == 0)
                return (ft_export(cmd->cmd + 1, &env, gc), g_exit_status);
            else if ((ft_strcmp(cmd->cmd[0], "unset")) == 0)
                return ft_unset(cmd->cmd + 1, &env);
            else if ((ft_strcmp(cmd->cmd[0], "exit")) == 0)
                return ft_exit(cmd->cmd + 1, gc);
        }
    }
    write_error(cmd->cmd[0], 2);
    return 127; // Command not found
}

void built_in(t_command *cmd, t_env *env, t_gc **gc)
{
    int save_in = -1;
    int save_out = -1;

    if (cmd->has_redirect)
        handle_builtin_redirection(cmd, &save_in, &save_out, 1);

    g_exit_status = execute_builtin_command(cmd, env, gc);

    if (cmd->has_redirect)
        handle_builtin_redirection(cmd, &save_in, &save_out, 0);
}
