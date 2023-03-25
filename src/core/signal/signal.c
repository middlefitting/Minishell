/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:54:07 by sechung           #+#    #+#             */
/*   Updated: 2023/03/25 13:44:28 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		write (1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	child_signal_handler(int signo)
{
	(void) signo;
	ft_putendl_fd("", STDERR_FILENO);
	exit(1);
}

void	default_signal(void)
{
	signal(SIGINT, new_prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_herdoc_signal(void)
{
	signal(SIGINT, child_signal_handler);
}

void	set_signal(pid_t pid)
{
	if (pid == 0)
	{
		signal(SIGINT, child_signal_handler);
		signal(SIGQUIT, child_signal_handler);
	}
	else
		signal(SIGINT, SIG_IGN);
}
