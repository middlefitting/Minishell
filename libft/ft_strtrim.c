/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:52:43 by sechung           #+#    #+#             */
/*   Updated: 2022/07/08 13:10:41 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;
	size_t	i;

	if (s1 == 0 || set == 0)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	i = 0;
	while (s1[start] && ft_strchr(set, s1[start]) && start < end)
		start++;
	while (i < end && ft_strchr(set, s1[end - i - 1]))
		i++;
	end = end - i;
	if (end <= start)
		return (ft_calloc(1, 1));
	return (ft_substr(s1, start, end - start));
}
