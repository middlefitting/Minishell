/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:55:18 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:19:15 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
