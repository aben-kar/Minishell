// #include "minishell.h"
#include "../minishell.h"

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	//k3ibiza
// 	//minishell> cat
// //^C
// //minishell> minishell$ ^C
// 	write(1, "minishell$ ", 11);
// }

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1); // print new line
	rl_replace_line("", 0); // cleari line dl input
	rl_on_new_line(); // tell readline you're at a new line
	rl_redisplay(); // reprint the prompt and buffer li kaykon deja msavi f readline, kat3awd tprompti
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
