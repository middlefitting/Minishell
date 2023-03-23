#include "parser.h"

void	env_update(t_token *env, char *name, char *content)
{
	free(env->content);
	free(name);
	env->content = content;
}

char	*get_env_name(char *raw)
{
	int		i;
	char	*name;

	i = 0;
	name = 0;
	while (raw[i] && raw[i] != '=')
		i++;
	while (!name)
		name = ft_substr(raw, 0, i);
	return (name);
}

char	*get_env_content(char *raw)
{
	char	*content;
	char	*target;

	content = 0;
	target = ft_strchr(raw, '=');
	if (!target)
		return (0);
	while (!content)
		content = ft_strdup(target + 1);
	return (content);
}

void	env_append(t_deque *envs, char *raw)
{
	t_token *temp;
	t_token	*env;
	char	*name;
	char	*content;

	name = get_env_name(raw);
	content = get_env_content(raw);
	temp = envs->top;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (env_update(temp, name, content));
		temp = temp->next;
	}
	env = get_env_token();
	env->name = name;
	env->content = content;
	append(envs, env);
}

void	env_init(t_data *data, char **envp)
{
	int 	i;

	i = 0;
	data->envs = get_deque();
	while (envp[i])
	{
		env_append(data->envs, envp[i]);
		i++;
	}
}
