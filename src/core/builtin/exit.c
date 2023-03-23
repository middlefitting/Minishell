#include "parser.h"
#include "exec.h"

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

int	exit_arg_check(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!ft_isdigit(content[i]))
			return (0);
		i++;
	}
}

void	ft_exit(t_simple_cmd *simple_cmd)
{
	if (simple_cmd->argv->size > 2)
	{
		print_exit_error_arg();
		g_exit_status = 1;
		return ;
	}
	if (simple_cmd->argv->size == 2 &&
		!exit_arg_check(simple_cmd->argv->top->next->content))
	{
		print_exit_error_digit(simple_cmd->argv->top->next->content);
		exit(255);
	}
	ft_putendl_fd("exit", 1);
	exit(0);
}
