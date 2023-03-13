/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:15:26 by sechung           #+#    #+#             */
/*   Updated: 2022/07/08 13:11:22 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_method(char **result)
{
	size_t	i;

	i = 0;
	while (result[i] != 0)
		free(result[i]);
	free(result);
}

size_t	ft_splitlen(char const *s, char c)
{
	size_t	result;

	result = 0;
	while (s[result])
	{
		if (s[result] == c)
			return (result);
		result++;
	}
	if (result > 0)
		return (result);
	return (0);
}

char	**ft_initialize(char const *s, size_t size, char c, char **result)
{
	size_t	temp;
	size_t	len;
	size_t	start;

	temp = 0;
	start = 0;
	while (temp < size)
	{
		len = ft_splitlen(s + start, c);
		if (len > 0)
		{
			result[temp] = ft_substr(s, start, len);
			start = start + len;
			if (result[temp] == 0)
			{
				free_method(result);
				return (0);
			}
			temp++;
		}
		start++;
	}
	return (result);
}

size_t	ft_count(char const *s, char c)
{
	size_t	i;
	size_t	result;
	size_t	len;

	i = 0;
	result = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (len > 0)
			{
				result++;
				len = 0;
			}
			i++;
			continue ;
		}
		len++;
		i++;
	}
	if (len > 0)
		result++;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	size;

	if (s == 0)
		return (0);
	size = ft_count(s, c);
	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (0);
	result[size] = 0;
	return (ft_initialize(s, size, c, result));
}
