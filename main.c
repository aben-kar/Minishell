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

			tokens = tokenize(input, &gc);				 // assumes tokenize may call gc_alloc()
			cmds = parse_tokens(tokens, &has_pipe, &gc); // same here
		
			// int i = 0;

			// while (input[i])
			// {
			// 	// if pipe ==> function pipe =1

			// 	// else without pipe ==> excute command
			// }
			if (input && *input)
			{
				if (has_pipe)
					printf("ila kayen pipe ==> %d\n", has_pipe); // ila kan lpipe at3tik 1 f result
				else
				{
					printf("ila makayenach pipe ==> %d\n", has_pipe); // daba ila makaynch lpipe at3tik 0 f result o ghat executi bla pipe
					execute_command(cmds, env_list);
				}
			}
		}
	}
}