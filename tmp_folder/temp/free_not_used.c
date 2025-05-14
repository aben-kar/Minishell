// #include "minishell.h"
#include "../minishell.h"

void	free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens->next;
        if (tokens->value) // only if not NULL
            free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}

void	free_commands(t_command *cmds)
{
    int i;
    t_command *tmp;

    while (cmds)
    {
        tmp = cmds->next;
        if (cmds->cmd)
        {
            i = 0;
            while (cmds->cmd[i])
            {
                free(cmds->cmd[i]);
                i++;
            }
            free(cmds->cmd);
        }
        free(cmds);
        cmds = tmp;
    }
}
