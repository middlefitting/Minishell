#include "exec.h"

void	m_echo(t_process *proc, t_deque *argv, int flag)
{
	t_token	*str;
	int		option;
	int		i;

	str = check_echo_option (argv, &option);
	while (str)
	{
		i = 0;
		while (str != NULL && str->content[i] != '\0')
			write (STDOUT_FILENO, &str->content[i++], 1);
		if (str->next)
			write (STDOUT_FILENO, " ", 1);
		str = str->next;
	}
	if (!option)
		write (STDOUT_FILENO, "\n", 1);
	if (proc->num_of_pipe == 0)
		recover_std (proc);
	mexit (flag, 0);
}

t_token	*check_echo_option(t_deque *argv, int *option)
{
	t_token	*str;

	*option = 0;
	str = argv->top->next;
	while (str != NULL && !ft_strcmp ("-n", str->content))
	{
		*option = 1;
		str = str->next;
	}
	return (str);
}

void	m_env(t_process *proc, int flag)
{
	t_token	*env;
	int		i;

	env = proc->envp->top;
	while (env)
	{
		i = 0;
		while (env->name[i] != '\0')
			write (STDOUT_FILENO, &env->name[i++], 1);
		write (STDOUT_FILENO, "=", 1);
		i = 0;
		while (env->content[i] != '\0')
			write (STDOUT_FILENO, &env->content[i++], 1);
		env = env->next;
		write (STDOUT_FILENO, "\n", 1);
	}
	if (proc->num_of_pipe == 0)
		recover_std (proc);
	mexit (flag, g_exit_status);
}

void	m_cd(t_process *proc, int flag)
{
	char	*path;
	char	*home;
	char	*temp;
	int		error;

	home = get_env (proc->envp, "HOME");
	path = 0;
	if (proc->pipe->cmd->simple_cmd->argv->top->next)
		path = proc->pipe->cmd->simple_cmd->argv->top->next->content;
	if (path == NULL && home != NULL)
		error = chdir (home);
	else
		error = chdir (path);
	if (error == ERROR && (home == NULL || path == NULL))
		path_error (path, home);
	else
		g_exit_status = 0;
	path = getcwd (NULL, 0);
	temp = ft_strjoin("PWD=", path);
	env_append(proc->envp, temp);
	free(path);
	free(temp);
	if (proc->num_of_pipe == 0)
		recover_std (proc);
	mexit (flag, g_exit_status);
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
