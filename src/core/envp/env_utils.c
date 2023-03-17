#include "parser.h"

char	*get_env(t_deque *envs, char *name)
{
	t_token	*env;

	env = envs->top;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->content);
		env = env->next;
	}
	return (0);
}
