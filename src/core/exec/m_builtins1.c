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
	char	*content;
	int		env_flag;
	int		i;

	env = proc->envp->top;
	env_flag = 0;
	if (proc->pipe->cmd->simple_cmd->argv->top->next == NULL)
		env_flag = 1;
	if (env_flag == 0)
	{
		content = proc->pipe->cmd->simple_cmd->argv->top->next->content;
		print_error ("env", content, 0);
	}
	write_env (env, env_flag);
	if (proc->num_of_pipe == 0)
		recover_std (proc);
	mexit (flag, g_exit_status);
}

void	write_env(t_token *env, int env_flag)
{
	int	i;

	i = 0;
	while (env && env_flag)
	{
		if (env->content)
		{
			i = 0;
			while (env->name[i] != '\0')
				write (STDOUT_FILENO, &env->name[i++], 1);
			i = 0;
			write (STDOUT_FILENO, "=", 1);
			while (env->content[i] != '\0')
				write (STDOUT_FILENO, &env->content[i++], 1);
			write (STDOUT_FILENO, "\n", 1);
		}
		env = env->next;
	}
}
