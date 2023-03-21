#include "parser.h"

void	ft_export(t_simple_cmd *simple_cmd, t_data *data)
{
	if (!simple_cmd)
		return ;
	if (simple_cmd->argv->size == 1)
		return ;
	else
	{

	}
}

void	ft_unset(t_simple_cmd *simple_cmd, t_data *data)
{
	char *name;

	if (simple_cmd->argv->size == 1 || simple_cmd->argv->size == 0)
		return ;
	name = get_env_name(simple_cmd->argv->top->next->content);
	remove_env(data->envs, name);
	free(name);
}
