#include "parser.h"

char	*join_line(char *dest, char *s)
{
	char	*new_line;
	char	*merge_line;

	new_line = 0;
	merge_line = 0;
	while (!merge_line)
		merge_line = ft_strdup(s);
	while (!new_line)
		new_line = ft_strjoin(dest, merge_line);
	free(dest);
	free(merge_line);
	return (new_line);
}

char	*substr_env(t_data *data, int s, int e)
{
	char	*name;
	char	*env;

	name = 0;
	while (!name)
		name = ft_substr(data->line, s + 1, e - s - 1);
	env = get_env(data->envs, name);
	free(name);
	return (env);
}

void	renew_line(t_data *data, int s, int e)
{
	char	*env;
	char	*new_line;

	new_line = 0;
	env = substr_env(data, s, e);
	while (!new_line)
		new_line = ft_substr(data->line, 0, s);
	if (env)
		new_line = join_line(new_line, env);
	new_line = join_line(new_line, &(data->line[e]));
	free(data->line);
	data->line = new_line;
}

void parse_env(t_data *data, int s)
{
	int		e;
	char	*env;

	e = s + 1;
	while (data->line[e] &&
			data->line[e] != '\'' &&
			data->line[e] != '\"' &&
			data->line[e] != '|' &&
			data->line[e] != '<' &&
			data->line[e] != '>' &&
			data->line[e] != '$' &&
			!white_space(data->line[e]))
		e++;
	if ((e - s) == 1)
		return;
	renew_line(data, s, e);
}

int	env_parser(t_data *data)
{
	int	i;
	int quote_flag;

	i = 0;
	quote_flag = 0;
	while (data->line[i])
	{
		if (data->line[i] == '\'' || data->line[i] == '\"')
			quote_flag = renew_quote_flag(quote_flag, data->line[i]);
		if (quote_flag == 0 && data->line[i] == '$')
			parse_env(data, i);
		if (!data->line[i])
			break;
		i++;
	}
	return (1);
}
