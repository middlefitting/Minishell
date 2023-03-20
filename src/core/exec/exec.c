# include "exec.h"

extern int	mexit_status;
void	exec(t_pipe *tree, t_deque *envp)
{
	t_process	*proc;
	proc = init_proc (tree, envp);
	if (proc->pipe->pipe == NULL)
	{
		check_redir (proc);
		if (proc->pipe->cmd->simple_cmd == NULL)
			return ;
		if (proc->pipe->cmd->simple_cmd->built_in_flag)
		{
			do_builtins (proc, 0);
			return ;
		}
	}
	// write (1, "init_success\n", 13);
	if (proc->pipe->pipe != NULL)
		do_pipe (proc, tree);
	// write (1, "pipe_success\n", 13);
	do_fork (proc, tree);//fork 실패시 예외처리 필요
	//write (1, "fork_success\n", 13);
	do_cmds (proc);
}

t_process	*init_proc(t_pipe *tree, t_deque *envp)
{
	t_process	*tmp;

	tmp = 0;
	while (!tmp)
		tmp =  ft_calloc(1, sizeof(t_process));
	tmp->pid = 1;
	tmp->pipe = tree;
	tmp->num_of_pipe = get_pipe_size (tree);
	tmp->fd_idx = 0;
	tmp->cmd = 0;
	tmp->envp = envp;
	tmp->fds = (int **) ft_calloc (tmp->num_of_pipe, sizeof (int *));
	while (tmp->fd_idx < tmp->num_of_pipe)
		tmp->fds[tmp->fd_idx++] = (int *) ft_calloc (2, sizeof (int));
	return (tmp);
}

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
		if (proc->pid == 0)
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
	if (proc->pipe->pipe != NULL)
		close_and_dup (proc);
	if (proc->pipe->cmd->redirects != NULL)
		check_redir (proc);
	if (proc->pipe->cmd->simple_cmd == NULL)
		return ;
	if (proc->pipe->cmd->simple_cmd->built_in_flag)
		do_builtins (proc, 1);
	else
		make_path (proc);
}

void	exit_proc(t_process *proc)
{
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	mexit_status = 0;
	while (i <= proc->num_of_pipe)
	{
		status = 0;
		pid = wait (&status);
		if (pid > 0)
			i++;
		if (proc->pid == pid)
			mexit_status = WEXITSTATUS(status);
	}
}

void	do_builtins(t_process *proc, int flag) //함수 실행 후 $?환경변수에 상태값 업데이트 필요
{
	char	*cmd;

	cmd = proc->pipe->cmd->simple_cmd->file_path->content;
	if (!ft_strcmp ("echo", cmd))
		m_echo(proc, proc->pipe->cmd->simple_cmd->argv, flag);
	else if (!ft_strcmp ("cd", cmd))
		m_cd(proc, flag);
	else if (!ft_strcmp ("pwd", cmd))
		m_pwd(proc, flag);
	else if (!ft_strcmp ("export", cmd))
		m_export(proc, flag);
	else if (!ft_strcmp ("unset", cmd))
		m_unset(proc, flag);
	else if (!ft_strcmp ("env", cmd))
		m_env(proc, flag);
	else if (!ft_strcmp ("exit", cmd))
		exit (0);
}