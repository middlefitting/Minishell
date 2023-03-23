#include "parser.h"
#include "exec.h"

void	envs_sort(char **envs)
{
	char	*temp;
	char	*pre;
	char	*next;
	int		i;
	int		j;

	i = -1;
	while (envs[++i])
	{
		j = i + 1;
		while (envs[j])
		{
			pre = get_env_name(envs[i]);
			next = get_env_name(envs[j]);
			if (ft_strcmp(pre, next) > 0)
			{
				temp = envs[i];
				envs[i] = envs[j];
				envs[j] = temp;
			}
			free(pre);
			free(next);
			j++;
		}
	}
}

void	print_export(t_deque *d_envs, int i)
{
	char	**envs;
	char	*name;
	char	*content;

	envs = get_envs_pointer(d_envs);
	envs_sort(envs);
	while (envs[i])
	{
		name = get_env_name(envs[i]);
		content = get_env_content(envs[i]);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(name, 1);
		if (content)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(content, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		free(name);
		free(content);
		i++;
	}
	free_envs_pointer(envs);
}

int	env_name_check(char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	if (ft_strlen(name) == 1 && name[0] == '_')
		return (-1);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return(0);
		i++;
	}
	return(1);
}

void	export_env(t_deque *d_envs, t_token *token, int *flag)
{
	char	*name;

	name = get_env_name(token->content);
	if(env_name_check(name) == 1)
		env_append(d_envs, token->content);
	else if (env_name_check(name) == 0)
	{
		*flag = 1;
		print_error("export", token->content, 2);
	}
	free(name);
}

void	ft_export(t_simple_cmd *simple_cmd, t_deque *d_envs)
{
	int		flag;
	t_token	*temp;

	flag = 0;
	// if (!simple_cmd)
		// return ;
	if (simple_cmd->argv->size == 1)
		print_export(d_envs, 0);
	else
	{
		temp = simple_cmd->argv->top->next;
		while (temp)
		{
			export_env(d_envs, temp, &flag);
			temp = temp->next;
		}
	}
	g_exit_status = flag;
}
