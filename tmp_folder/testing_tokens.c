#include "minishell.h"

void print_command_structure(t_command *cmds)
{
	int i = 1;
	while (cmds)
	{
		printf("=== Command %d ===\n", i++);
		printf("Arguments:\n");
		for (int j = 0; cmds->cmd && cmds->cmd[j]; j++)
			printf("  argv[%d]: %s\n", j, cmds->cmd[j]);

		printf("Redirects:\n");
		t_redirect *r = cmds->redirects;
		while (r)
		{
			char *type;
			if (r->type == 0) type = ">";
			else if (r->type == 1) type = ">>";
			else if (r->type == 2) type = "<";
			else if (r->type == 3) type = "<<";
			else type = "unknown";
			printf("  %s %s\n", type, r->filename);
			r = r->next;
		}
		cmds = cmds->next;
	}
}
