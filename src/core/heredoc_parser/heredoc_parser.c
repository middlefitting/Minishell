/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:25:03 by sechung           #+#    #+#             */
/*   Updated: 2023/03/24 19:05:33 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substr_heredoc_env(char *line, t_deque *envs, int s, int e)
{
	char	*name;
	char	*env;

	name = 0;
	while (!name)
		name = ft_substr(line, s + 1, e - s - 1);
	env = get_env(envs, name);
	free(name);
	return (env);
}

char	*renew_heredoc_line(char *line, int *s_e, int *index, t_deque *envs)
{
	char	*env;
	char	*new_line;

	new_line = 0;
	env = substr_heredoc_env(line, envs, s_e[0], s_e[1]);
	while (!new_line)
		new_line = ft_substr(line, 0, s_e[0]);
	if (env)
		new_line = join_line(new_line, env);
	new_line = join_line(new_line, &(line[s_e[1]]));
	free(line);
	line = new_line;
	if (env)
	{
		*index += (ft_strlen(env) - 1);
		free(env);
	}
	return (line);
}

char	*parse_herdoc_env(char *line, int s, int *index, t_deque *envs)
{
	int		e;
	int		s_e[2];

	e = s + 1;
	if (line[e] == '?')
		e++;
	else
	{
		while (line[e]
			&& (ft_isalpha(line[s + 1]) || line[s + 1] == '_')
			&& (ft_isalnum(line[e]) || line[e] == '_'))
			e++;
	}
	if ((e - s) == 1)
		return (line);
	s_e[0] = s;
	s_e[1] = e;
	return (renew_heredoc_line(line, s_e, index, envs));
}

char	*heredoc_parser(char *line, t_deque *envs)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			line = parse_herdoc_env(line, i, &i, envs);
		if (!line[i])
			break ;
		i++;
	}
	return (line);
}
