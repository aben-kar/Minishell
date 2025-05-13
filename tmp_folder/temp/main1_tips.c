#include "minishell.h"

int	g_exit_status = 0;

int	main(void)
{
	/*
	 Update exit status after commands
	Wherever you execute commands (in your execution code), after fork() and waitpid(), save the status:

		int	status;

		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else
			g_exit_status = 1;
		This ensures $? reflects the last command's exit code.

		// SINCE IM ALREADY DETECTING IF THERE IS A $? IN MY EXPAND_VAR FUNC
		// I JUST NEED TO LET THE EXECUTOR KNOW TO HANDLE ACCORDINGLY
	*/
	/*
	✅ Your job is done here.
		Let your teammate handling execution:

		Set g_exit_status properly after each command.

		That value will automatically get picked up by your expand_var() logic when a future command contains $?.
	*/
	char	*line;

	setup_signals();
	write(1, "minishell> ", 11);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (line[0] != '\n')
		{
			// call tokenizer/parser/executor here
		}
		free(line);
		write(1, "minishell> ", 11);
	}
	return (0);
}
