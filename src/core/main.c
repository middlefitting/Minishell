#include "minishell.h"
#include "exec.h"
#include "parser.h"

void	arg_check(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("Not Support\n", 1);
		exit(1);
	}
}

void	eof_check(char *str)
{
	if (str == NULL)
	{
		write (1, "exit\n", 5);
		exit (0);
	}
}

void	exit_check(char *str)
{
	if (!ft_strcmp (str, "exit"))
	{
		write (1, "exit\n", 5);
		exit (0);
	}
}

int main (int argc, char *argv[], char **envp)
{
	struct termios t;
	int check;
	t_data data;

	arg_check(argc);
	if (tcgetattr (STDIN_FILENO, &t) == -1)
		return (1);
	init_tflag (&t);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1)
		return (1);
	if (tgetent (NULL, "xterm-256color") == -1)
		return (1);
	init_data(&data);
	env_init(&data, envp);
	while (1)
	{
		default_signal();
		data.line  = readline ("minishell$ ");
		eof_check(data.line);
		if (ft_strcmp(data.line , ""))
			add_history (data.line);
		// exit_check(data.line);
		if (parse(&data))
			exec (data.tree, data.envs);
		free_data(&data);
	}
	return (0);
}
