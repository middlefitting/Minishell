#include "parser.h"

extern int	g_exit_status;

void	new_prompt_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		write (1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_signal_handler(int signo)
{
	if (signo == SIGINT)
		ft_putendl_fd("", STDERR_FILENO);
	else if (signo == SIGQUIT)
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
	exit(128 + signo);
}

void	default_signal(void)
{
	signal(SIGINT, new_prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_herdoc_signal(pid_t pid)
{
	if (pid == 0)
	{
		signal(SIGINT, child_signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		signal(SIGINT, SIG_IGN);
}

void	set_signal(pid_t pid)
{
	if (pid == 0)
	{
		signal(SIGINT, child_signal_handler);
		// if (heredoc)
		// 	signal(SIGQUIT, SIG_IGN);
		// else
		signal(SIGQUIT, child_signal_handler);
	}
	else
		signal(SIGINT, SIG_IGN);
}