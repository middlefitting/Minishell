/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:25:03 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:33:26 by jhwang2          ###   ########.fr       */
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
	if (env)
	{
		new_line = join_line(new_line, "\'");
		new_line = join_line(new_line, env);
		new_line = join_line(new_line, "\'");
	}
	new_line = join_line(new_line, &(data->line[s_e[1]]));
	free(data->line);
	data->line = new_line;
	if (env)
		*index += (ft_strlen(env) + 1);
	free(env);
}

void	parse_env(t_data *data, int s, int *index, int quote_flag)
{
	int		e;
	int		s_e[2];

	e = s + 1;
	if (data->line[e] == '?')
		e++;
	else
	{
		while (data->line[e]
			&& (ft_isalpha(data->line[s + 1]) || data->line[s + 1] == '_')
			&& (ft_isalnum(data->line[e]) || data->line[e] == '_'))
			e++;
	}
	if ((e - s) == 1)
		return ;
	s_e[0] = s;
	s_e[1] = e;
	renew_line(data, s_e, index, quote_flag);
}

int	env_parser(t_data *data)
{
	int	i;
	int	quote_flag;

	i = 0;
	quote_flag = 0;
	while (data->line[i])
	{
		if (data->line[i] == '\'' || data->line[i] == '\"')
			quote_flag = renew_quote_flag(quote_flag, data->line[i]);
		if (quote_flag != 1 && data->line[i] == '$')
			parse_env(data, i, &i, quote_flag);
		if (!data->line[i])
			break ;
		i++;
	}
	return (1);
}
