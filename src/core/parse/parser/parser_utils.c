#include "parser.h"

int	get_pipe_size(t_pipe *pipe)
{
	int		result;
	t_pipe	*next;

	result = 0;
	next = pipe->pipe;
	while (next)
	{
		result++;
		next = next->pipe;
	}
	return (result);
}

void	set_built_in_flag(t_cmd *cmd, t_token *token)
{
	if (ft_strcmp(token->content, "echo") == 0 ||
		ft_strcmp(token->content, "cd") == 0 ||
		ft_strcmp(token->content, "pwd") == 0 ||
		ft_strcmp(token->content, "export") == 0 ||
		ft_strcmp(token->content, "unset") == 0 ||
		ft_strcmp(token->content, "env") == 0 ||
		ft_strcmp(token->content, "exit") == 0)
		cmd->simple_cmd->built_in_flag = 1;
	else
		cmd->simple_cmd->built_in_flag = 0;
}
