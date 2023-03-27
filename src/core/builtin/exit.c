/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: middlefitting <middlefitting@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:20:27 by sechung           #+#    #+#             */
/*   Updated: 2023/03/27 12:49:16 by middlefitti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_error_digit(char *msg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

void	print_exit_error_arg(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", 2);
}

void	single_arg_check(t_simple_cmd *simple_cmd, int num_of_pipe)
{
	if (simple_cmd->argv->size == 1)
	{
		g_exit_status = 0;
		if (num_of_pipe == 0)
			ft_putendl_fd("exit", 1);
		exit(0);
	}
}

void	numeric_check(int flag, t_simple_cmd *simple_cmd)
{
	if (!flag)
	{
		g_exit_status = 255;
		print_exit_error_digit(simple_cmd->argv->top->next->content);
		exit(255);
	}
}

void	ft_exit(t_simple_cmd *simple_cmd, int num_of_pipe)
{
	int result;
	int	flag;

	flag = 1;
	single_arg_check(simple_cmd, num_of_pipe);
	result = ft_longtoi(simple_cmd->argv->top->next->content, &flag);
	numeric_check(flag, simple_cmd);
	if (simple_cmd->argv->size > 2)
	{
		print_exit_error_arg();
		g_exit_status = 1;
		return ;
	}
	g_exit_status = (result % 256);
	if (num_of_pipe == 0)
		ft_putendl_fd("exit", 1);
	exit(result % 256);
}
