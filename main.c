#include "minishell.h"

// define global variable
int g_exit_status = 0;

int main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
	{
		char *input;
		t_token *tokens;
		t_command *cmds;
		int has_pipe;
		t_gc *gc;
		t_env *env_list = init_copier_env(envp);
		// t_env *env = ft_copier_env(env_list, envp);

		while (1)
		{
			setup_signals();
			input = readline("minishell$ ");

			if (input == NULL)
			{
				printf("exit\n");
				break;
			}
			// add_history

			tokens = tokenize(input, &gc);				 // assumes tokenize may call gc_alloc()
			cmds = parse_tokens(tokens, &has_pipe, &gc); // same here

			if (input && *input)
			{
				if (has_pipe)
					execute_multi_pipe(cmds, env_list);
				else
					execute_command(cmds, env_list);
			}
		}
		free(input);	  // Msahi l'input
		gc_free_all(&gc); // Nadi l'garbage collector
	}
}