/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_shell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:58:10 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/13 16:23:03 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef MINISHELL_H
// #define MINISHELL_H


// // # include <stdio.h>
// // # include <string.h>
// // # include <stdlib.h>
// // # include <stdint.h>
// // # include <unistd.h>
// // # include <fcntl.h>
// // # include <sys/wait.h>
// // #include <stdbool.h>
// // # include "libft/libft.h"
// // #include <linux/limits.h> // For PATH_MAX
// // #include <sys/stat.h> // for stat
// // #include <readline/readline.h>
// // #include <readline/history.h>

// typedef struct stat t_stat;

// // typedef struct s_env
// // {
// //     char *key;            // ex: PATH
// //     char *value;          // ex: /usr/bin:/bin
// //     bool    has_value;  // equal exists ? 1 : 0
// //     struct s_env *next;
// // } t_env;


// // typedef struct s_mypipex // structe deyal l pipe
// // {
// //     int fd[2];     // file descriptors dyal pipe
// //     char **cmd1;
// //     char **cmd2;
// //     char *infile;
// //     char *outfile;
// //     // int		in_file;
// // 	// int		out_file;
// // } t_mypipex;


// typedef struct s_command {
//     char **cmd;               // ex: ["ls", "-l", "-a"]
//     char *infile;             // ex: "file.txt" ila kayn <
//     char *outfile;            // ex: "output.txt" ila kayn > ou >>
//     int  append;              // 0 = > , 1 = >> < <<
//     bool  has_pipe;            // true ila kayn pipe ou false ila makayenach
//     // struct s_command *next;   // command li jaya mn ba3d (pipe)
// } t_command;

// // void execute_command(t_command *shell, char **envp);
// void execute_command(t_command *shell, t_env *env);
// // BUILT-IN COMMAND
// int ft_echo(char **args);
// // int ft_cd(char **args, char **envp);
// int ft_cd(char **args, t_env *env);
// int ft_pwd(void);
// // int ft_copier_env(t_env *env, char **envp);
// t_env *ft_copier_env(t_env *env, char **envp);
// t_env *init_copier_env(char **envp);
// int ft_export(char **args, t_env **env);
// void insert_at_end(t_env **head, char *key, char *value);
// char **env_to_array(t_env *env);
// int ft_env(t_env *env);
// int check_plus(char *args);
// // void key_with_equal(char *args, char *key, char *value, t_env **env);
// int key_with_equal(char *arg, char **key, char **value, t_env **env);
// int key_with_plus(char *arg, char **key, char **value, t_env **env);
// int ft_unset(char **args, t_env **env);
// int ft_exit(char **args);

// #endif
