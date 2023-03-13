/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:41:56 by sechung           #+#    #+#             */
/*   Updated: 2022/07/07 17:04:57 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*copy;
	size_t	size;

	i = 0;
	size = ft_strlen(s);
	copy = malloc(sizeof(char) * (size + 1));
	if (copy == 0)
		return (0);
	while (i < size)
	{
		copy[i] = s[i];
		i++;
	}	
	copy[i] = 0;
	return (copy);
}
