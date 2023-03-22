#include "parser.h"
#include "exec.h"

char	*get_env(t_deque *envs, char *name)
{
	t_token	*env;
	char	*result;

	result = 0;
	if (ft_strcmp(name, "?") == 0)
	{
		while (!result)
			result = ft_itoa(g_exit_status);
		return (result);
	}
	env = envs->top;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			if (!env->content)
				return (0);
			while (!result)
				result = ft_strdup(env->content);
			return (result);
		}
		env = env->next;
	}
	return (0);
}

void	remove_env(t_deque *envs, char *name)
{
	t_token *env;
	int		s;

	s = 0;
	if (!envs->top)
		return ;
	while (ft_strcmp(name, envs->top->name) != 0 &&
			s < envs->size)
	{
		env = popleft(envs);
		append(envs, env);
		s++;
	}
	if (s <= envs->size)
	{
		env = popleft(envs);
		free_token(env);
	}
}

char	**get_envs_pointer(t_deque *envs)
{
	char	**envs_pointer;
	t_token	*env;
	int		s;

	envs_pointer = 0;
	s = 0;
	while (!envs_pointer)
		envs_pointer = ft_calloc(envs->size + 1, sizeof(char *));
	while (s < envs->size)
	{
		env = popleft(envs);
		while (!envs_pointer[s])
			envs_pointer[s] = ft_calloc(1, sizeof(char));
		envs_pointer[s] = join_line(envs_pointer[s], env->name);
		if (env->content)
		{
			envs_pointer[s] = join_line(envs_pointer[s], "=");
			envs_pointer[s] = join_line(envs_pointer[s], env->content);
		}
		append(envs, env);
		s++;
	}
	return (envs_pointer);
}

void	free_envs_pointer(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		free(envs[i]);
		i++;
	}
	free(envs[i]);
	free(envs);
}
