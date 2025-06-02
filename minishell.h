/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:23:09 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/02 16:29:16 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <linux/limits.h> // For PATH_MAX
# include <sys/stat.h> // for stat
# include <readline/readline.h>
# include <readline/history.h> // add_history
# include "libft/libft.h"
# include "parser/gc.h"
# include <errno.h>

// about herdoc
#define	REDIR_OUT 0 // normalment hada khaso ikon REDIR_OUT
#define	REDIR_APPEND 1 // normalmment hada khaso ikon REDIR_APPEND
#define	REDIR_IN 2 // normalment hada khaso ikon REDIR_IN
#define	REDIR_HEREDOC 3 // HADA RAH
#define CYAN "\033[36m"	
#define RESET "\033[0m"

extern int	g_exit_status; // global varible
typedef struct stat t_stat;

typedef struct s_token {
	char	*value;
	struct s_token *next;
}	t_token;

typedef struct s_redirect {
	char	*filename;
	int		type;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command { // about excution
	char	**cmd; // command
	t_redirect	*redirects; // linked list of
	bool	has_redirect; // (true == kayen || false == makayench)
	struct s_command *next; // for pipelines
}	t_command;

typedef struct s_env // about env
{
    char *key;            // ex: PATH
    char *value;          // ex: /usr/bin:/bin
    struct s_env *next;
} t_env;

typedef struct s_herdoc_line
{
	char				*line;
	struct s_herdoc_line	*next;
}	t_herdoc_line;

// Built-in command
int ft_echo(char **args);
int ft_cd(char **args, t_env *env, t_gc **gc);
int ft_pwd(void);
void ft_export(char **args, t_env **env, t_gc **gc);
int ft_env(t_env *env);
int ft_unset(char **args, t_env **env);
int ft_exit(char **args, t_gc **gc);
// function helper about Built-in
// t_env *ft_copier_env(t_env *env, char **envp, t_gc **gc);
t_env *init_copier_env(char **envp, t_gc **gc);
void insert_at_end(t_env **head, char *key, char *value, t_gc **gc);
void print_error(char *key, t_gc **gc);
// bool check_plus(char *args);
int equal_or_plus(char *arg);
void key_with_equal(char *arg, char **key, char **value, t_env **env, t_gc **gc);
void key_with_plus(char *arg, char **key, char **value, t_env **env, t_gc **gc);
// execution
void execute_command(t_command *shell, t_env *env, t_gc **gc);
char **env_to_array(t_env *env, t_gc **gc);
char *find_executable_path(t_command *shell, t_env *envp, t_gc **gc);
bool check_command(t_command *cmd);
void execute_external_cmd(t_command *cmd, t_env *env, t_gc **gc);
void built_in(t_command *cmd, t_env *env, t_gc **gc);
void write_error(char *cmd, int error_code);
// multi-pipe
void execute_multi_pipe(t_command *cmd, t_env *env, t_gc **gc);
void excute_cmd_in_pipe(t_command *cmd, t_env *env, t_gc **gc);
int handle_exit_status(int status);
bool first_char(char *key);
int alpha(char *args);
bool check_key(char *args);
void handel_redirection(t_command *cmd);

// ---------------------------------------------------------------------

void		bash_syntax_error(const char *token);
void		bash_unclosed_quote_error(char quote);
t_token		*add_token(t_token *last, char *value, t_gc **gc);
t_token		*tokenize(const char *input, t_gc **gc);
char		*get_env_val(const char *key, t_env *env);
// char		*expand_var(char *word, t_gc **gc, t_env *env);
char		*expand_word(const char *word, t_gc **gc, t_env *env);
char		*create_here_doc(char *delimiter);
int			is_redir(const char *s);
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
bool		handle_redirection(t_command *cmd, t_token **tokens,
	t_gc **gc, t_env *env, int type);
bool		handle_argument(t_command *cmd, t_token *token,
	t_gc **gc, t_env *env);
t_command   *parse_tokens(t_token *tokens, int *has_pipe, t_gc **gc, t_env *env);
// void        free_tokens(t_token *tokens);
// void        free_commands(t_command *cmds);
bool	is_quoted_delimiter(const char *delimiter);
char	*strip_quotes(const char *str, t_gc **gc);
char	*generate_temp_filename(t_gc **gc);
char	*handle_heredoc(const char *delimiter, t_gc **gc, t_env *env);
bool	skip_quoted(const char *input, int *i);
int		contains_equal(const char *input, int *i);
bool	skip_post_equal(const char *input, int *i);
char	*extract_token_value(const char *input, int start, int end, t_gc **gc);
// char	*expand_inside_double_quotes(const char *str, t_gc **gc, t_env *env);
int		handle_dollar(const char *word, char **res, int i, t_gc **gc, t_env *env);
char    *expand_word_always_expand(const char *word, t_gc **gc, t_env *env);
// void	expand_command(t_command *cmd, t_env *env, t_gc **gc);
// gc libft funcs
void	*ft_calloc_gc(size_t nelem, size_t size, t_gc **gc);
char	*ft_itoa_gc(int n, t_gc **gc);
char	*ft_strdup_gc(const char *s1, t_gc **gc);
char	*ft_substr_gc(const char *s, unsigned int start, size_t len, t_gc **gc);
char	*ft_strjoin_gc(const char *s1, const char *s2, t_gc **gc);
char	*ft_strjoin_char_gc(const char *s, char c, t_gc **gc);
char	**ft_split_gc(char const *s, char *c, t_gc **gc);
// test
// void print_command_structure(t_command *cmds);
// int count_args(char **args);


#endif