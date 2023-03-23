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
		ft_exit(proc->pipe->cmd->simple_cmd);
	if (flag)
		exit (g_exit_status);
	else
		return ;
}

void	m_cd(t_process *proc, int flag)
{
	char	*path;
	char	*tmp;
	int		opt_flag;


	path = 0;
	if (proc->pipe->cmd->simple_cmd->argv->top->next)
		path = proc->pipe->cmd->simple_cmd->argv->top->next->content;
	path = check_cdopt (proc, path, &opt_flag);
	tmp = getcwd (NULL, 0);
	check_patherror (path, path, opt_flag);
	update_pwd (proc, tmp);
	if (path)
		free (path);
	if (proc->num_of_pipe == 0)
		recover_std (proc);
	mexit (flag, g_exit_status);
}

void	update_pwd(t_process *proc, char *tmp)
{
	char	*path;

	path = ft_strjoin ("OLDPWD=", tmp);
	if (tmp)
		free (tmp);
	env_append(proc->envp, path);
	free (path);
	tmp = getcwd (NULL, 0);
	path = ft_strjoin ("PWD=", tmp);
	env_append(proc->envp, path);
	if (path)
		free(path);
	if (tmp)
		free(tmp);
}

char	*check_cdopt(t_process *proc, char *path, int *opt_flag)
{
	if (path == NULL || !ft_strcmp (path, "~"))
	{
		*opt_flag = 1;
		return (get_env (proc->envp, "HOME"));
	}
	else if (!ft_strcmp (path, "-"))
	{
		*opt_flag = 2;
		return (get_env (proc->envp, "OLDPWD"));
	}
	else
	{
		*opt_flag = 0;
		return (ft_strdup (path));
	}
}

void	check_patherror(char *path, char *home, int opt_flag)
{
	int	error;
	int	i;

	error = 0;
	i = 0;
	if (path == NULL && home == NULL)
		error = 1;
	else
	{
		error = chdir (path);
		if (error != 1 && opt_flag == 2)
		{
			while (path[i])
				write (1, &path[i++], 1);
			write (1, "\n", 1);
		}
	}
	if (error)
		path_error (path, home, opt_flag);
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
