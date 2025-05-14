#include "minishell.h"

// define global variable
int g_exit_status = 0;
/*

❗Important
You now need to replace malloc/calloc inside tokenize, parse_tokens, etc.
	with gc_alloc(size, &gc) where appropriate. For example:

char *val = gc_alloc(len + 1, &gc);

This way, all allocations go through the GC and are automatically freed.

*/
// int main(int ac, char **av, char **envp)
// {
// 	(void)av;
// 	// (void)envp;
// 	if (ac == 1)
// 	{
// 		char *line;
// 		t_token *tokens;
// 		t_command *cmds = NULL;
// 		int has_pipe;
// 		t_gc *gc;
// 		t_env *env_list = init_copier_env(envp);
// 		t_env *env = ft_copier_env(env_list, envp);

// 		while (1)
// 		{
// 			setup_signals();
// 			write(1, "minishell$ ", 11);
// 			line = get_next_line(0); // no readline, works with ctrl-D too
// 			if (!line)
// 			{
// 				write(1, "exit\n", 5);
// 				break;
// 			}
// 			if (line[0] == '\n')
// 			{
// 				free(line);
// 				continue;
// 			}

// 			gc = NULL; // reset GC for each loop

// 			tokens = tokenize(line, &gc);				 // assumes tokenize may call gc_alloc()
// 			cmds = parse_tokens(tokens, &has_pipe, &gc); // same here
// 														 // Inside your while(1) loop, after parse_tokens():
// 			t_command *current = cmds;

// 			if (current)
// 			{
// 				printf ("hena\n");
// 				execute_command(current, env);
// 			}
// 			// while (current)
// 			// {
// 			// 	printf("Command: %s\n", current->cmd[0]); // Print first arg (e.g., "ls")
// 			// 	printf("Args: ");
// 			// 	for (int i = 0; current->cmd[i]; i++)
// 			// 		printf("[%s] ", current->cmd[i]);
// 			// 	printf("\n");

// 			// 	// printf("Has pipe? %d\n", current->has_pipe); // Or equivalent field
// 			// 	// printf("In FD: %d, Out FD: %d\n", current->in_fd, current->out_fd);

// 			// 	current = current->next;
// 			// 	// printf("-----\n");
// 			// }

// 			// printf ("command ==> %s\n", cmds->cmd);

// 			// if (cmds && cmds->cmd && cmds->cmd[0])
// 			// {
// 			// 	// if (ft_strcmp(cmds->cmd[0], "echo") == 0 && cmds->cmd[1])
// 			// 	// {
// 			// 	// 	write(1, cmds->cmd[1], ft_strlen(cmds->cmd[1]));
// 			// 	// 	write(1, "\n", 1);
// 			// 	// 	g_exit_status = 0;
// 			// 	// }
// 			// 	// else
// 			// 	// {
// 			// 	// 	write(2, "Command not found\n", 18);
// 			// 	// 	g_exit_status = 127;
// 			// 	// }

// 			// 	execute_command(cmds, env); //
// 			// }
// 			// else
// 			// 	g_exit_status = 2;

// 			// Free everything
// 			free(line);
// 			// free_tokens(tokens);
// 			// free_commands(cmds);
// 			gc_free_all(&gc); // clean all GC-tracked memory
// 		}
// 	}
// 	return (0);
// }


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
		t_env *env = ft_copier_env(env_list, envp);

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
					printf("%d\n", has_pipe); // ila kan lpipe at3tik 1 f result
				else
				{
					printf("%d\n", has_pipe); // daba ila makaynch lpipe at3tik 0 f result o ghat executi bla pipe
					execute_command(cmds, env);
				}
			}
		}
	}
}