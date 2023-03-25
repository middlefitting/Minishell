/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:53:28 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 21:07:29 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	renew_quote_flag(int flag, char c)
{
	if (flag == 0)
	{
		if (c == '\'')
			return (1);
		else if (c == '\"')
			return (2);
	}
	else if (flag == 1)
	{
		if (c == '\'')
			return (0);
	}
	else if (flag == 2)
	{
		if (c == '\"')
			return (0);
	}
	return (flag);
}

int	quote_check(char *line)
{
	int	ind;
	int	flag;

	ind = 0;
	flag = 0;
	while (line[ind])
	{
		if (line[ind] == '\'' || line[ind] == '\"')
			flag = renew_quote_flag(flag, line[ind]);
		ind++;
	}
	if (flag == 0)
		return (1);
	else if (flag == 1)
		print_parse_error("unclosed quote");
	else if (flag == 2)
		print_parse_error("unclosed dquote");
	return (0);
}
