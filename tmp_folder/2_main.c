/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:57:54 by acben-ka          #+#    #+#             */
/*   Updated: 2025/05/13 17:32:38 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../minishell.h"

int g_exit_status = 0;



int main(int ac, char **av, char **envp)
{
    (void)av;
    if (ac == 1)
    {
        t_command shell;
        // shell.has_pipe = false;
        char *input;
        t_env *env_list = init_copier_env(envp);
        t_env *env = ft_copier_env(env_list, envp);
        
        while (1)
        {
            input = readline("minishell$ ");
            
            // Check if readline returned NULL (Ctrl+D)
            if (input == NULL)
            {
                printf("exit\n");
                break;
            }
            
            // Add to history only if not empty
            // if (*input)
            //     add_history(input);
                
            if (input && ft_strcmp(input, "out") == 0)
            {
                free(input);
                break;
            }

            if (input && *input) // Only process if input exists and is not empty
            {
                char **args = ft_split(input, " ");
                
                if (args)
                {
                    // int i = 0;
                    // shell.has_pipe = false; // Reset pipe flag

                    // // Process any pipes
                    // while (args[i])
                    // {
                    //     if (ft_strcmp(args[i], "|") == 0)
                    //     {
                    //         write(2, "Pipe detected\n", 14);
                    //         shell.has_pipe = true;
                    //         break;
                    //     }
                    //     i++;
                    // }

                    // if (shell.has_pipe)
                    // {
                    //     // Handle pipe functionality
                    // }
                    // if () // execute command
                    // {
                    shell.cmd = args;
                    execute_command(&shell, env);
                    // }
                    
                    // Free allocated memory
                    // for (i = 0; args[i]; i++)
                    //     free(args[i]);
                    // free(args);
                }
            }
            
            // free(input); // Always free input outside the conditional
        }
        
        // Free environment list before exit
        // [code to free env_list and env]
    }
    else
    {
        printf("Usage: ./minishell\n");
    }
    return 0;
}
