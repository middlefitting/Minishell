/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtins1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:36:12 by sechung           #+#    #+#             */
/*   Updated: 2023/03/25 13:58:24 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (str != NULL && is_option (str->content))
	{
		*option = 1;
		str = str->next;
	}
	return (str);
}

int	is_option(char *content)
{
	int	i;

	i = 0;
	if (content == NULL)
		return (0);
	if (content[i++] != '-')
		return (0);
	while (content[i])
	{
		if (content[i++] != 'n')
			return (0);
	}
	return (1);
}

void	m_env(t_process *proc, int flag)
{
	t_token	*env;
	char	*content;
	int		env_flag;

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
