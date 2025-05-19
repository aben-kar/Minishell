// #include "minishell.h"
#include "../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	//k3ibiza
	//minishell> cat
//^C
//minishell> minishell$ ^C
	write(1, "minishell$ ", 11);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
