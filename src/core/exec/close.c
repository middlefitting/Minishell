#include "exec.h"

void	close_and_dup(t_process *proc)
{
	if (proc->cmd == 2)
	{
		close (proc->fds[0][READ]);
		dup2 (proc->fds[0][WRITE], STDOUT_FILENO);
		close (proc->fds[0][WRITE]);
	}
	else if (proc->pipe->pipe == NULL)
	{
		close (proc->fds[proc->cmd - 3][WRITE]);
		dup2 (proc->fds[proc->cmd - 3][READ], STDIN_FILENO);
		close (proc->fds[proc->cmd - 3][READ]);
	}
	else
	{
		dup2 (proc->fds[proc->cmd - 3][READ], STDIN_FILENO);
		close (proc->fds[proc->cmd - 3][READ]);
		dup2 (proc->fds[proc->cmd - 2][WRITE], STDOUT_FILENO);
		close (proc->fds[proc->cmd - 2][WRITE]);
	}
	close_fds (proc, 0);
}

void	close_fds(t_process *proc, int check_parent)
{
	int	i;

	i = -1;
	while (++i < proc->num_of_pipe)
	{
		if (i == proc->cmd - 2 && !check_parent)
		{
			if (proc->cmd == 2 || proc->pipe->pipe == NULL)
				continue ;
			close (proc->fds[i - 1][WRITE]);
			close (proc->fds[i][READ]);
		}
		else
		{
			if (i == proc->cmd - 3 && !check_parent)
				continue ;
			close (proc->fds[i][READ]);
			close (proc->fds[i][WRITE]);
		}
	}
	if (proc->num_of_pipe == 1)
		close_fd (proc);
}

void	close_fd(t_process *proc)
{
	if (proc->cmd == 2)
		close (proc->fds[0][READ]);
	else if (proc->cmd == 3)
		close (proc->fds[0][WRITE]);
}
