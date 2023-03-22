#include "exec.h"

void	do_pipe(t_process *proc, t_pipe *tree)
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

int	do_fork(t_process *proc, t_pipe *tree)
{
	t_pipe	*tmp;
	int		i;

	tmp = proc->pipe;
	i = 0;
	while (i <= proc->num_of_pipe)
	{
		if (proc->pid > 0)
			proc->pid = fork ();
		else
			return (0);
		if (proc->pid == 0) //signal setting
		{
			proc->pipe = tmp;
			proc->cmd = i + 2;
		}
		else if (proc->pid < 0)
			exit (1);
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
