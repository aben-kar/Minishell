// #ifndef MINISHELL_H
// # define MINISHELL_H

// #include "../libft/libft.h"
// #include "../get_next_line/get_next_line.h"
// #include "gc.h"
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <signal.h>
// // #include <stdio.h>

// #define	REDIR_IN 0
// #define	REDIR_OUT 1
// #define	REDIR_APPEND 2
// #define	REDIR_HEREDOC 3

// extern int	g_exit_status;

// typedef struct s_token {
// 	char	*value;
// 	struct s_token *next;
// }	t_token;

// typedef struct s_redirect {
// 	char	*filename;
// 	int		type; // (0: >, 1: >>, 2: <, 3: <<)
// 	struct s_redirect	*next;
// }	t_redirect;

// typedef struct s_command {
// 	char	**argv; // command
// 	t_redirect	*redirects; // linked list of redirections
// 	struct s_command *next; // for pipelines
// }	t_command;

// t_token		*add_token(t_token *last, char *value, t_gc **gc);
// t_token		*tokenize(const char *input, t_gc **gc);
// char		*expand_var(char *word, t_gc **gc);
// char		*create_here_doc(char *delimiter);
// int			is_redir(char *s);
// int			redir_type(char	*s);
// int			ft_isspace(char c);
// int			is_operator(char c);
// int			ft_strcmp(const char *s1, const char *s2);
// char		*ft_strndup(const char *s, size_t n, t_gc **gc);
// void		setup_signals(void);
// void		handle_sigint(int sig);
// t_redirect	*add_redir(t_redirect *list, char *filename, int type, t_gc **gc);
// char    	**argv_add(char **argv, const char *value, t_gc **gc);
// t_command	*add_command(t_command *list, t_command *new);
// t_command   *parse_tokens(t_token *tokens, int *has_pipe, t_gc **gc);
// void        free_tokens(t_token *tokens);
// void        free_commands(t_command *cmds);
// // gc libft funcs
// void	*ft_calloc_gc(size_t nelem, size_t size, t_gc **gc);
// char	*ft_itoa_gc(int n, t_gc **gc);
// char	*ft_strdup_gc(const char *s1, t_gc **gc);
// char	*ft_substr_gc(const char *s, unsigned int start, size_t len, t_gc **gc);

// #endif