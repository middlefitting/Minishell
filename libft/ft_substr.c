/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: middlefitting <middlefitting@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:50:17 by sechung           #+#    #+#             */
/*   Updated: 2023/03/17 21:24:49 by middlefitti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cut;
	size_t	s_len;
	size_t	i;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_calloc(1, 1));
	if (s_len < len)
		len = s_len;
	i = 0;
	cut = (char *) malloc(sizeof(char) * (len + 1));
	if (cut == 0)
		return (0);
	while (i < len && i + start < s_len)
	{
		cut[i] = s[i + start];
		i++;
	}
	cut[len] = 0;
	return (cut);
}
