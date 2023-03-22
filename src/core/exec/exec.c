#include "exec.h"

void	exec(t_pipe *tree, t_deque *envp)
{
	t_process	*proc;

	proc = init_proc (tree, envp);
	mk_heredoc (proc);
	if (!proc->num_of_pipe)
		if (check_isbuiltins(proc))
			return ;
	if (proc->num_of_pipe)
		do_pipe (proc, tree);
	do_fork (proc, tree);//fork 실패시 예외처리 필요
	do_cmds (proc);
	free_proc (proc);
}

t_process	*init_proc(t_pipe *tree, t_deque *envp)
{
	t_process	*tmp;

	tmp = 0;
	while (!tmp)
		tmp = ft_calloc(1, sizeof(t_process));
	tmp->pid = 1;
	tmp->pipe = tree;
	tmp->num_of_pipe = get_pipe_size (tree);
	tmp->fd_idx = 0;
	tmp->cmd = 0;
	tmp->envp = envp;
	tmp->heredoc_file = (char **)ft_calloc
		(tmp->num_of_pipe + 1, sizeof (char *));
	tmp->fds = (int **)ft_calloc(tmp->num_of_pipe, sizeof (int *));
	while (tmp->fd_idx < tmp->num_of_pipe)
		tmp->fds[tmp->fd_idx++] = (int *)ft_calloc(2, sizeof (int));
	tmp->fd_idx = 0;
	save_std (tmp);
	return (tmp);
}

void	exit_proc(t_process *proc)
{
	pid_t	pid;
	char	*cur_status;
	int		status;
	int		i;

	i = 0;
	while (i <= proc->num_of_pipe)
	{
		status = 0;
		pid = wait (&status);
		if (pid > 0)
			i++;
		if (proc->pid == pid)
			g_exit_status = WEXITSTATUS(status);
	}
	rm_heredoc ();
}
