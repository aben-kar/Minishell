/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:22:59 by zaakrab           #+#    #+#             */
/*   Updated: 2025/06/03 01:44:10 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// define global variable
int	g_exit_status = 0;

// void print_node(t_command *head)
// {
//     while (head)
//     {
//         printf("----- Command Node -----\n");

//         // Print argv
//         int i = 0;
//         while (head->cmd && head->cmd[i])
//         {
//             printf("cmd[%d] = [%s]\n", i, head->cmd[i]);
//             i++;
//         }

//         // Print redirections (use a temp pointer so we don't lose original list)
//         t_redirect *redir = head->redirects;
//         while (redir)
//         {
//             int type = redir->type;
//             char *smiyadyaltype = NULL;
//             switch (type)
//             {   
//             case 0:
//                 smiyadyaltype = "REDIR_IN";
//                 break;
//             case 1:
//                 smiyadyaltype = "REDIR_OUT";
//                 break;
//             case 2:
//                 smiyadyaltype = "REDIR_APPEND";
//                 break;
//             case 3:
//                 smiyadyaltype = "REDIR_HEREDOC";
//                 break;
//             default:
//                 break;
//             }
//             printf("redir: { type: %s, filename: %s }\n", smiyadyaltype, redir->filename);
//             redir = redir->next;
//         }

//         // Print pipe info
//         //printf("pipe_in: %d, pipe_out: %d\n", head->bo,);

//         printf("----------------------------------------------------------------------------------------\n\n\n");

//         head = head->next;
//     }
// }

static void	handle_input(char *input, t_env **env_list, t_gc **gc)
{
	t_token		*tokens;
	t_command	*cmds;
	int			has_pipe;

	tokens = tokenize(input, gc);
	if (!tokens)
		return ;
	cmds = parse_tokens(tokens, &has_pipe, gc, *env_list);
	if (!cmds)
		return ;
	// print_node(cmds);
	if (has_pipe)
		execute_multi_cmd(cmds, *env_list, gc);
	else
		execute_command(cmds, env_list, gc);
}

static void	minishell_loop(t_env *env_list, t_gc **gc)
{
	char	*input;

	while (1)
	{
		setup_signals();
		rl_catch_signals = 0;
		input = readline(CYAN "minishell$ " RESET);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		handle_input(input, &env_list, gc);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_gc	*gc;
	t_env	*env_list;

	(void)av;
	if (ac != 1)
		return (1);
	gc = NULL;
	env_list = init_copier_env(envp, &gc);
	minishell_loop(env_list, &gc);
	clear_history();
	gc_free_all(&gc);
	return (0);
}
