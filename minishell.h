/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:23:09 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/15 15:49:57 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
#include <stdbool.h>
# include "libft/libft.h"
#include <linux/limits.h> // For PATH_MAX
#include <sys/stat.h> // for stat
#include <readline/readline.h>
#include <readline/history.h> // add_history
#include "parser/gc.h"

#define	REDIR_IN 0
#define	REDIR_OUT 1
#define	REDIR_APPEND 2
#define	REDIR_HEREDOC 3

extern int	g_exit_status; // global varible

typedef struct stat t_stat;

typedef struct s_token {
	char	*value;
	struct s_token *next;
}	t_token;

typedef struct s_redirect {
	char	*filename;
	int		type; // (0: >, 1: >>, 2: <, 3: <<)
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command { // about excution
	char	**cmd; // command
	t_redirect	*redirects; // linked list of redirections
	struct s_command *next; // for pipelines
}	t_command;

typedef struct s_env
{
    char *key;            // ex: PATH
    char *value;          // ex: /usr/bin:/bin
    struct s_env *next;
} t_env;


void execute_command(t_command *shell, t_env *env);
// BUILT-IN COMMAND
int ft_echo(char **args);
// int ft_cd(char **args, char **envp);
int ft_cd(char **args, t_env *env);
int ft_pwd(void);
// int ft_copier_env(t_env *env, char **envp);
t_env *ft_copier_env(t_env *env, char **envp);
t_env *init_copier_env(char **envp);
int ft_export(char **args, t_env **env);
void insert_at_end(t_env **head, char *key, char *value);
char **env_to_array(t_env *env);
int ft_env(t_env *env);
int check_plus(char *args);
// void key_with_equal(char *args, char *key, char *value, t_env **env);
int key_with_equal(char *arg, char **key, char **value, t_env **env);
int key_with_plus(char *arg, char **key, char **value, t_env **env);
int ft_unset(char **args, t_env **env);
int ft_exit(char **args);
void print_error(char *key);

// ---------------------------------------------------------------------

t_token		*add_token(t_token *last, char *value, t_gc **gc);
t_token		*tokenize(const char *input, t_gc **gc);
char		*expand_var(char *word, t_gc **gc);
char		*create_here_doc(char *delimiter);
int			is_redir(char *s);
int			redir_type(char	*s);
int			ft_isspace(char c);
int			is_operator(char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strndup(const char *s, size_t n, t_gc **gc);
void		setup_signals(void);
void		handle_sigint(int sig);
t_redirect	*add_redir(t_redirect *list, char *filename, int type, t_gc **gc);
char    	**argv_add(char **argv, const char *value, t_gc **gc);
t_command	*add_command(t_command *list, t_command *new);
t_command   *parse_tokens(t_token *tokens, int *has_pipe, t_gc **gc);
// void        free_tokens(t_token *tokens);
// void        free_commands(t_command *cmds);
// gc libft funcs
void	*ft_calloc_gc(size_t nelem, size_t size, t_gc **gc);
char	*ft_itoa_gc(int n, t_gc **gc);
char	*ft_strdup_gc(const char *s1, t_gc **gc);
char	*ft_substr_gc(const char *s, unsigned int start, size_t len, t_gc **gc);


#endif