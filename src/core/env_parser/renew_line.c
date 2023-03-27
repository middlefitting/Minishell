/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renew_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: middlefitting <middlefitting@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:18:09 by sechung           #+#    #+#             */
/*   Updated: 2023/03/27 12:58:15 by middlefitti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_pre_token_type(t_data *data, int *index, int quote_flag)
{
	int	i;
	int	white_flag;

	i = *index;
	white_flag = 0;
	while ((i >= 0)
		&& ((quote_flag != 0)
			|| (data->line[i] != '|'
				&& data->line[i] != '<'
				&& data->line[i] != '>')))
	{
		if (!white_space(data->line[i]) && white_flag == 1)
			break ;
		if (quote_flag == 0 && white_space(data->line[i]))
			white_flag = 1;
		quote_flag = renew_quote_flag(quote_flag, data->line[i]);
		i--;
	}
	if (i < 0)
		return (DEFAULT);
	if (data->line[i] == '<' && i > 0 && data->line[i - 1] == '<')
		return (HEREDOC);
	if (data->line[i] == '<' || data->line[i] == '>')
		return (REDIRECTION);
	return (DEFAULT);
}

char	*join_env_line(char *env, char *new_line, int quote_flag)
{
	if (env)
	{
		if (!quote_flag)
			new_line = join_line(new_line, "\'");
		new_line = join_line(new_line, env);
		if (!quote_flag)
			new_line = join_line(new_line, "\'");
	}
	return (new_line);
}

void	renew_index(int *index, char *env, int quote_flag)
{
	if (env)
	{
		if (!quote_flag)
			*index += (ft_strlen(env) + 1);
		else
			*index += (ft_strlen(env) - 1);
		free(env);
	}
}

void	renew_line(t_data *data, int *s_e, int *index, int quote_flag)
{
	char	*env;
	char	*new_line;
	int		pre_type;

	pre_type = get_pre_token_type(data, index, quote_flag);
	if (pre_type == HEREDOC)
		return ;
	new_line = 0;
	env = substr_env(data, s_e[0], s_e[1]);
	while (!new_line)
		new_line = ft_substr(data->line, 0, s_e[0]);
	new_line = join_env_line(env, new_line, quote_flag);
	new_line = join_line(new_line, &(data->line[s_e[1]]));
	free(data->line);
	data->line = new_line;
	renew_index(index, env, quote_flag);
}
