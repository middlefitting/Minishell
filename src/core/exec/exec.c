#include "exec.h"

void	exec(t_pipe *tree, t_deque *envp)
{
	t_process	*proc;

	proc = init_proc (tree, envp);
	is_heredoc(proc);
	if (!proc->num_of_pipe && !proc->heredoc_flag)
		if (check_isbuiltins(proc))
			return ;
	if (proc->heredoc_flag)
	{
		if (heredoc_fork (proc))
		{
			free_proc (proc);
			return ;
		}
	}
	fork_and_pipe (proc, 0);
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
	tmp->heredoc_flag = 0;
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
	int		status;
	int		i;

	i = 0;
	while (i <= proc->num_of_pipe)
	{
		pid = wait (&status);
		if (pid > 0 || pid == -1)
			i++;
		if (proc->pid == pid)
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			g_exit_status = 128 + WTERMSIG (status);
			if (WTERMSIG (status) == 2)
				ft_putendl_fd("", STDERR_FILENO);
			else if (WTERMSIG (status) == 3)
				ft_putendl_fd("Quit: 3", STDOUT_FILENO);
		}
	}
	rm_heredoc ();
}
