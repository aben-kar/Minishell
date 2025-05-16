#include "minishell.h"

// define global variable
int g_exit_status = 0;

int main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
	{
		char		*input;
		t_token		*tokens;
		t_command	*cmds;
		int			has_pipe;
		t_gc		*gc = NULL;
		t_env		*env_list = init_copier_env(envp, &gc);
		t_env		*env;

		while (1)
		{
			setup_signals();
			env = ft_copier_env(env_list, envp, &gc);
			input = readline("minishell$ ");

			if (input == NULL)
			{
				printf("exit\n");
				break;
			}
			// add_history
			if (*input) // ignore empty inputs
				add_history(input); // t9dr tnavigi lhistory b arrows..
			tokens = tokenize(input, &gc);				 // assumes tokenize may call gc_alloc()
			cmds = parse_tokens(tokens, &has_pipe, &gc, env); // same here
			if (input && *input)
			{
				if (has_pipe)
					execute_multi_pipe(cmds, env_list, &gc);
				else
					execute_command(cmds, env_list, &gc);
				/*
					mohim daba t9dr tkhdm had logic for redirections:
					if (cmd->has_redirect) {
    					// handle redirections
					}
					chi 7aja b7al hka...
				*/
			}
		}
		free(input);
		gc_free_all(&gc);
	}
}