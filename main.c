/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:47:57 by acben-ka          #+#    #+#             */
/*   Updated: 2025/06/22 16:48:49 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static void	handle_input(char *input, t_env **env_list, t_gc **gc)
{
	t_token		*tokens;
	t_command	*cmds;
	int			has_pipe;

	cmds = NULL;
	tokens = tokenize(input, gc);
	if (!tokens)
		return ;
	cmds = parse_tokens(tokens, &has_pipe, gc, *env_list);
	if (!cmds)
		return ;
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
			exit(g_exit_status);
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
