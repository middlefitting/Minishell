# include "exec.h"

extern int	mexit_status;
void	make_path(t_process *proc)
{
	char	**execve_option;
	char	**path_splitted;
	char	*cmd;
	int		i;

	execve_option = get_option (proc);
	cmd = proc->pipe->cmd->simple_cmd->file_path->content;
	cmd = m_strjoin ("/", cmd);
	i = 0;
	if (!get_env (proc->envp, "PATH"))
	{
		write (2, "command not found\n", 18);
		mexit_status = 127;
		exit (127);
	}
	path_splitted = m_split (get_env (proc->envp, "PATH"), ':');
	do_execve (proc, path_splitted, execve_option, cmd);
}

char	**get_option(t_process *proc)
{
	t_deque	*argv;
	char	**option;
	int		num_of_opt;
	int		i;

	argv = proc->pipe->cmd->simple_cmd->argv;
	num_of_opt = argv->size;
	option = NULL;
	while (!option)
		option = (char **)m_calloc (num_of_opt + 1, sizeof (char *));
	i = 0;
	while (argv->top != NULL)
	{
		option[i] = argv->top->content;
		argv->top = argv->top->next;
	}
	return (option);
}

void	do_execve(t_process *proc, char **path_splitted, char **option, char *cmd)
{
	char	**envp;
	char	*path_cmd;
	int		i;

	i = 0;
	envp = get_envs_pointer (proc->envp);
	while (path_splitted[i])
	{
		path_cmd = m_strjoin (path_splitted[i], cmd);
		execve (path_cmd, option, envp);
		free (path_cmd);
		i++;
	}
	if (execve (cmd, option, envp) < 0)
		write (2, "command not found\n", 18);
	mexit_status = 127;
	close_fds (proc, 1);
	exit (127);
}