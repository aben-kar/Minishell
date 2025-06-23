/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:23:09 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/23 17:47:29 by acben-ka         ###   ########.fr       */
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
# include <linux/limits.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "libft/libft.h"
# include "parser/gc.h"
# include "parser/helper_struct.h"

# define REDIR_OUT 0
# define REDIR_APPEND 1
# define REDIR_IN 2
# define REDIR_HEREDOC 3
# define CYAN "\033[36m"
# define RESET "\033[0m"

extern int				g_exit_status;

typedef struct stat		t_stat;

typedef struct s_token
{
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_redirect
{
	char				*filename;
	int					type;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_command
{
	char				**cmd;
	t_redirect			*redirects;
	bool				has_redirect;
	struct s_command	*next;
}						t_command;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_herdoc_line
{
	char					*line;
	struct s_herdoc_line	*next;
}						t_herdoc_line;

typedef struct s_pipeline
{
	int					fd[2];
	int					save_fd;
	int					id;
	int					cmd_count;
	pid_t				*pids;
}						t_pipeline;

typedef struct s_variable
{
	int					j;
	char				**built_in;
	char				*line;
	char				*eq;
	char				*val;
	char				*final;
}						t_variable;

typedef struct s_to_array
{
	int					i;
	int					size;
	char				**envp;
}						t_to_array;

typedef struct s_vrr
{
	char				*key;
	char				*value;
}						t_vrr;

int						ft_echo(char **args);
int						ft_cd(char **args, t_env *env, t_gc **gc);
int						ft_pwd(void);
int						ft_env(t_env *env);
int						ft_unset(char **args, t_env **env);
int						ft_exit(char **args, t_gc **gc);
int						equal_or_plus(char *arg);
int						handle_exit_status(int status);
int						alpha(char *args);
int						validate_filename(char *filename, int setup);
int						contains_space(char *str);
int						handle_home_cd(t_env *env);
int						validate_path(char *path);
int						change_directory(char *path, t_env **env, t_gc **gc);
int						count_commands(t_command *cmd);
int						is_redir(const char *s);
int						redir_type(char *s);
int						ft_isspace(char c);
int						is_operator(char c);
int						ft_strcmp(const char *s1, const char *s2);
int						handle_dollar(const char *word, int i,
							t_expand_helper *ctx);
int						handle_exit_code(t_expand_helper *ctx);
int						handle_simple_dollar(t_expand_helper *ctx);
int						get_key_end_index(const char *word, int i);
int						handle_dollar_inner(const char *word, int i,
							t_expand_helper *ctx);
int						handle_char(const char *word, int i,
							t_expand_helper *ctx);
char					**env_to_array(t_env *env, t_gc **gc);
char					*find_executable_path(t_command *shell, t_env *envp,
							t_gc **gc);
char					*check_direct_path(t_command *shell);
char					*search_in_path_dirs(t_command *shell, t_env *envp,
							t_gc **gc);
char					*my_strjoin(char *s1, char *s2, t_gc **gc);
char					*ft_itoa_gc(int n, t_gc **gc);
char					*ft_strdup_gc(const char *s1, t_gc **gc);
char					*ft_substr_gc(const char *s, unsigned int start,
							size_t len, t_gc **gc);
char					*ft_strjoin_gc(const char *s1, const char *s2,
							t_gc **gc);
char					*ft_strjoin_char_gc(const char *s, char c, t_gc **gc);
char					**ft_split_gc(char const *s, char *c, t_gc **gc);
char					*get_env_val(const char *key, t_env *env);
char					*expand_word(const char *word, t_gc **gc, t_env *env);
char					*ft_strndup(const char *s, size_t n, t_gc **gc);
char					*generate_temp_filename(t_gc **gc);
char					*handle_heredoc(const char *delimiter, t_gc **gc,
							t_env *env);
char					**argv_add(char **argv, const char *value, t_gc **gc);
char					*strip_quotes(const char *str, t_gc **gc);
char					*expand_word_always_expand(const char *word, t_gc **gc,
							t_env *env);
void					insert_at_end(t_env **head, char *key, char *value,
							t_gc **gc);
void					print_error(char *key, t_gc **gc);
void					ft_export(char **args, t_env **env, t_gc **gc);
void					key_with_plus(char *arg, t_vrr *var, t_env **env,
							t_gc **gc);
void					key_with_equal(char *arg, t_vrr *var, t_env **env,
							t_gc **gc);
void					execute_command(t_command *shell, t_env **env,
							t_gc **gc);
void					execute_external_cmd(t_command *cmd, t_env *env,
							t_gc **gc);
void					built_in(t_command *cmd, t_env **env, t_gc **gc);
void					write_error(char *cmd, int error_code);
void					execute_multi_cmd(t_command *cmd, t_env *env,
							t_gc **gc);
void					excute_cmd_in_pipe(t_command *cmd, t_env *env,
							t_gc **gc);
void					handel_redirection_1(t_command *cmd);
void					ft_env_null(t_env **head, t_gc **gc);
void					process_env_line(t_env **head, char *envp_line,
							t_gc **gc);
void					print_export(t_env **env, t_gc **gc);
void					redir_in(t_redirect *redir);
void					redir_out(t_redirect *redir);
void					redir_append(t_redirect *redir);
void					redir_without_cmd(t_command *cmd);
void					setup_child_process(t_command *current, t_pipeline *vr,
							t_env *env, t_gc **gc);
void					handle_parent_process(pid_t *pids, int *i,
							t_pipeline *vr, t_command *current);
void					wait_for_all(pid_t *pids, int cmd_count);
void					bash_syntax_error(const char *token);
void					bash_unclosed_quote_error(char quote);
void					skip_whitespace(const char *input, int *i);
void					setup_signals(void);
void					handle_sigint(int sig);
void					*ft_calloc_gc(size_t nelem, size_t size, t_gc **gc);
bool					is_in_pipe(void);
bool					check_command(t_command *cmd);
bool					check_key(char *args);
bool					first_char(char *key);
bool					multiple_key(t_env *env, char *key);
bool					is_quoted_delimiter(const char *delimiter);
bool					skip_quoted(const char *input, int *i);
char					*remove_all_quotes(const char *input, t_gc **gc);
char					*get_delimiter(const char *raw_delim, t_gc **gc);
bool					handle_argument(t_command *cmd, t_token *token,
							t_minus_param *ctx);
bool					handle_redirection(t_command *cmd, t_token **tokens,
							t_minus_param *ctx, int type);
pid_t					fork_process(void);
t_env					*init_copier_env(char **envp, t_gc **gc);
t_token					*add_token(t_token *last, char *value, t_gc **gc);
t_token					*tokenize(const char *input, t_gc **gc);
t_command				*parse_tokens(t_token *tokens, int *has_pipe,
							t_gc **gc, t_env *env);
t_command				*add_command(t_command *list, t_command *new);
t_redirect				*add_redir(t_redirect *list, char *filename, int type,
							t_gc **gc);

#endif