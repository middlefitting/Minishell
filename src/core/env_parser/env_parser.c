/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:25:03 by sechung           #+#    #+#             */
/*   Updated: 2023/03/24 19:05:54 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
