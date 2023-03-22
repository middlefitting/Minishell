#include "exec.h"

extern int	mexit_status;

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
	if (flag)
		exit (mexit_status);
	else
		return ;
}
