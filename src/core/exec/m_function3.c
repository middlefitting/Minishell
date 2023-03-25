/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_function3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:38:21 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:17:50 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_heredoc(t_process *proc)
{
	t_redirects	*redirects;
	t_pipe		*pipe;

	pipe = proc->pipe;
	while (pipe)
	{
		redirects = pipe->cmd->redirects;
		while (redirects)
		{
			if (!ft_strcmp (redirects->redirect->type->content, "<<"))
				proc->heredoc_flag = 1;
			redirects = redirects->redirects;
		}
		pipe = pipe->pipe;
	}
}

void	recover_std(t_process *proc)
{
	dup2 (proc->std_in, STDIN_FILENO);
	close (proc->std_in);
	dup2 (proc->std_out, STDOUT_FILENO);
	close (proc->std_out);
}

void	save_std(t_process *proc)
{
	proc->std_in = dup (STDIN_FILENO);
	proc->std_out = dup (STDOUT_FILENO);
}

void	mexit(int flag, int mexit_status)
{
	g_exit_status = mexit_status;
	if (flag)
		exit (g_exit_status);
	else
		return ;
}

int	heredoc_fork(t_process *proc)
{
	pid_t	pid;
	int		status;

	proc->pid = fork();
	if (proc->pid == 0)
	{
		proc->pid = 1;
		mk_heredoc(proc);
		fork_and_pipe (proc, 1);
		exit (g_exit_status);
	}
	else
	{
		signal (SIGINT, SIG_IGN);
		pid = wait(&status);
		if (proc->pid == pid)
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			g_exit_status = WTERMSIG (status);
			ft_putendl_fd("", STDERR_FILENO);
			return (1);
		}
	}
	return (1);
}
