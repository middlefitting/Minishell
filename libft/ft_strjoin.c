/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:09:14 by sechung           #+#    #+#             */
/*   Updated: 2022/07/13 16:58:18 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size_s1;
	size_t	size_s2;
	char	*dest;

	if (s1 == 0 || s2 == 0)
		return (0);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	dest = malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (dest == 0)
		return (0);
	dest[size_s1 + size_s2] = 0;
	ft_memcpy(dest, s1, size_s1);
	ft_memcpy(dest + size_s1, s2, size_s2);
	return (dest);
}
