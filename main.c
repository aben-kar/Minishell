#include "minishell.h"

// define global variable
int g_exit_status = 0;

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

int main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
	{
		char		*input;
		t_token		*tokens;
		t_command	*cmds = NULL;
		int			has_pipe;
		t_gc		*gc = NULL;
		t_env		*env_list = init_copier_env(envp, &gc);
		// t_env		*env;

		while (1)
		{
			setup_signals();
			// print_command_structure(cmds); // testing tokens only
			// env = ft_copier_env(env_list, envp, &gc);
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
			cmds = parse_tokens(tokens, &has_pipe, &gc, env_list); // same here
			// function deyal debag (print_node) li katb9a t3awd l structure dyal commands.
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
			free(input);
		}
		clear_history();
		gc_free_all(&gc);
	}
}