#include "../minishell.h"

t_redirect	*add_redir(t_redirect *list, char *filename, int type, t_gc **gc)
{
	t_redirect	*new;
    t_redirect	*tmp;

    new = NULL;
    tmp = NULL;
    new = gc_alloc(sizeof(t_redirect), gc);
	new->filename = filename;
	new->type = type;
	new->next = NULL;
	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (list);
}

char    **argv_add(char **argv, const char *value, t_gc **gc)
{
	int     i;
    int     j;
	char    **new_argv;

    i = 0;
	while (argv && argv[i])
		i++;
	new_argv = gc_alloc(sizeof(char *) * (i + 2), gc);
	if (!new_argv)
		return (NULL);
    j = -1;
    while (++j < i)
		new_argv[j] = argv[j];
	new_argv[i] = ft_strdup_gc(value, gc);
	new_argv[i + 1] = NULL;
	return (new_argv);
}

t_command	*add_command(t_command *list, t_command *new)
{
    t_command *tmp;

    tmp = NULL;
	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (list);
}

t_command *parse_tokens(t_token *tokens, int *has_pipe, t_gc **gc, t_env *env)
{
    t_command   *cmds;
    char        *filename;
    char        *expanded;
    int         type;
    t_command   *cmd;

    expanded = NULL;
    cmd = NULL;
    cmds = NULL;
    if (!tokens)
        return (NULL);
    if (tokens && ft_strcmp(tokens->value, "|") == 0)
    {
        bash_syntax_error("|");
        return (NULL);
    }
    *has_pipe = 0;
    while (tokens)
    {
        cmd = ft_calloc_gc(1, sizeof(t_command), gc);
        if (!cmd)
            return (NULL);
        while (tokens && ft_strcmp(tokens->value, "|") != 0)
        {
            if (is_redir(tokens->value))
            {
                type = redir_type(tokens->value);
                tokens = tokens->next;
                if (!tokens)
                {
                    bash_syntax_error(NULL);
                    return (NULL);
                }
                if (is_redir(tokens->value) || ft_strcmp(tokens->value, "|") == 0)
                {
                    bash_syntax_error(tokens->value);
                    return (NULL);
                }
                filename = expand_word(tokens->value, gc, env);
                cmd->redirects = add_redir(cmd->redirects, filename, type, gc);
                cmd->has_redirect = true;
            }
            else
            {
                expanded = expand_word(tokens->value, gc, env);
                if (!expanded)
                    return (NULL);
				cmd->cmd = argv_add(cmd->cmd, expanded, gc);
            }
            tokens = tokens->next;
        }
        cmds = add_command(cmds, cmd);
        if (tokens && (!tokens->next || ft_strcmp(tokens->next->value, "|") == 0))
        {
            bash_syntax_error("|");
            return (NULL);
        }
        if (tokens)
        {
            *has_pipe = 1;
            tokens = tokens->next;
        }
    }
    return (cmds);
}
