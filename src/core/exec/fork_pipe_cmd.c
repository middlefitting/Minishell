/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:35:42 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:17:28 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_and_pipe(t_process *proc, int flag)
{
	if (proc->num_of_pipe)
		do_pipe (proc);
	if (do_fork (proc, 0))
	{
		if (flag)
			exit (1);
		else
			return ;
	}
	do_cmds (proc);
}

void	do_pipe(t_process *proc)
{
	int	i;

	i = 0;
	while (i < proc->num_of_pipe)
	{
		if (pipe (proc->fds[i]) < 0)
			exit (1);
		i++;
	}
}

int	do_fork(t_process *proc, t_pipe *tmp)
{
	int		i;

	tmp = proc->pipe;
	i = 0;
	while (i <= proc->num_of_pipe)
	{
		if (proc->pid > 0)
			proc->pid = fork ();
		else
			return (0);
		if (proc->pid == 0)
		{
			proc->pipe = tmp;
			proc->cmd = i + 2;
		}
		else if (proc->pid < 0)
		{
			fork_error ();
			return (1);
		}
		if (tmp != NULL)
			tmp = tmp->pipe;
		i++;
	}
	return (0);
}

void	do_cmds(t_process *proc)
{
	if (proc->pid == 0)
		do_cmd (proc);
	else
	{
		if (proc->num_of_pipe)
			close_fds (proc, 1);
		exit_proc (proc);
	}
}

void	do_cmd(t_process *proc)
{
	if (proc->num_of_pipe)
		close_and_dup (proc);
	if (proc->pipe->cmd->redirects != NULL)
		check_redir (proc);
	if (proc->pipe->cmd->simple_cmd == NULL)
		exit(g_exit_status);
	if (proc->pipe->cmd->simple_cmd->built_in_flag)
		do_builtins (proc, 1);
	else
		make_path (proc);
}
