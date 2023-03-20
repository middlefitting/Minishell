#include "exec.h"

extern int	mexit_status;
void	m_echo(t_process *proc, t_deque *argv, int flag)
{
	t_token	*str;
	int		option;
	int		i;

	option = 0;
	popleft (argv);
	str = popleft (argv);
	if (str != NULL && !ft_strcmp ("-n", str->content))
		option = 1;
	else if (str)
		appendleft (argv, str);
	while (str)
	{
		i = 0;
		str = popleft (argv);
		while (str != NULL && str->content[i] != '\0')
			write (1, &str->content[i++], 1);
		if (argv->top)
			write (1, " ", 1);
	}
	if (!option)
		write (1, "\n", 1);
	mexit_status = 0;
	mexit (flag);
}

void mexit(int flag)
{
	if (flag)
		exit (0);
	else
		return ;
}
void	m_env(t_process *proc, int flag)
{
	t_token *env;
	int		i;

	env = proc->envp->top;
	while (env)
	{
		i = 0;
		while (env->name[i] != '\0')
			write (1, &env->name[i++], 1);
		write (1, "=", 1);
		i = 0;
		while (env->content[i] != '\0')
			write (1, &env->content[i++], 1);
		env = env->next;
	}
	mexit_status = 0;
	if (flag)
		exit (0);
	else
		return ;
}

void	m_cd(t_process *proc, int flag)
{
	char	*path;
	char	*home;
	int		error;

	home = get_env (proc->envp, "HOME");
	path = proc->pipe->cmd->simple_cmd->argv->top->next->content;
	if (path == NULL)
		error = chdir (home);
	else
		error = chdir (path);
	if (error == ERROR)
		path_error (path);
	if (flag)
		exit (mexit_status);
	else
		return ;

}

void	path_error(char *path)
{
	struct stat	file;

	mexit_status = 1;
	if (stat(path, &file) == ERROR)
	{
		if (errno == ENOENT)
			write (1, "No such file or directory\n", 26);
		else if (file.st_mode != S_IFDIR)
			write (1, "Not a directory\n", 16);
	}
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
		mexit_status = 1;
		if (flag)
			exit (0);
		else
			return ;
	}
	while (path[i] != '\0')
		write (1, &path[i++], 1);
	write (1, "\n", 1);
	free (path);
	mexit_status = 0;
	if (flag)
		exit (0);
	else
		return ;
}
void		m_export(t_process *proc, int flag)
{
	return ;
}
void		m_unset(t_process *proc, int flag)
{
	return ;
}