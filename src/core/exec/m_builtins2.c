#include "exec.h"

int	check_isbuiltins(t_process *proc)
{
	if (proc->pipe->cmd->simple_cmd == NULL)
	{
		check_redir (proc);
		recover_std (proc);
		free_proc (proc);
		return (1);
	}
	if (proc->pipe->cmd->simple_cmd->built_in_flag)
	{
		check_redir (proc);
		do_builtins (proc, 0);
		recover_std (proc);
		free_proc (proc);
		return (1);
	}
	return (0);
}

void	do_builtins(t_process *proc, int flag)
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
		ft_export(proc->pipe->cmd->simple_cmd, proc->envp);
	else if (!ft_strcmp ("unset", cmd))
		ft_unset(proc->pipe->cmd->simple_cmd, proc->envp);
	else if (!ft_strcmp ("env", cmd))
		m_env(proc, flag);
	else if (!ft_strcmp ("exit", cmd))
		exit (0);
	if (flag)
		exit (g_exit_status);
	else
		return ;
}

void	m_cd(t_process *proc, int flag)
{
	char	*path;
	char	*home;
	char	*temp;
	int		error;

	home = get_env (proc->envp, "HOME");
	error = 0;
	path = 0;
	if (proc->pipe->cmd->simple_cmd->argv->top->next)
		path = proc->pipe->cmd->simple_cmd->argv->top->next->content;
	check_patherror (0, path, home);
	path = getcwd (NULL, 0);
	temp = ft_strjoin("PWD=", path);
	env_append(proc->envp, temp);
	free(path);
	free(temp);
	free(home);
	if (proc->num_of_pipe == 0)
		recover_std (proc);
	mexit (flag, g_exit_status);
}

void	check_patherror(int error, char *path, char *home)
{
	if (path == NULL && home != NULL)
		error = chdir (home);
	else if (path == NULL && home == NULL)
		error = 1;
	else
		error = chdir (path);
	if (error)
		path_error (path, home);
	else
		g_exit_status = 0;
	return ;
}

void	m_pwd(t_process *proc, int flag)
{
	char	*path;
	int		i;

	i = 0;
	path = getcwd (NULL, 0);
	if (path == NULL)
	{
		free (path);
		g_exit_status = 1;
		mexit (flag, g_exit_status);
	}
	while (path[i] != '\0')
		write (STDOUT_FILENO, &path[i++], 1);
	write (STDOUT_FILENO, "\n", 1);
	free (path);
	if (proc->num_of_pipe == 0)
		recover_std (proc);
	mexit (flag, g_exit_status);
}
