/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:22:51 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:26:48 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char *argv[], char **envp)
{
	struct termios	t;
	t_data			data;

	(void) argv;
	arg_check(argc);
	if (tcgetattr (STDIN_FILENO, &t) == -1)
		return (1);
	init_tflag (&t);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == (-1)
		|| tgetent (NULL, "xterm-256color") == -1)
		return (1);
	init_data(&data);
	env_init(&data, envp);
	while (1)
	{
		default_signal();
		data.line = readline ("minishell$ ");
		eof_check(data.line);
		if (ft_strcmp(data.line, ""))
			add_history (data.line);
		if (parse(&data))
			exec (data.tree, data.envs);
		free_data(&data);
	}
	return (0);
}
