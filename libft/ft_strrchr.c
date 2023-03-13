/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:29:24 by sechung           #+#    #+#             */
/*   Updated: 2022/07/07 15:13:01 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	c_c;
	size_t	s_size;

	c_c = (char) c;
	s_size = ft_strlen(s);
	while (s_size != 0 && *(s + s_size) != c_c)
		s_size--;
	if (s[s_size] == c_c)
		return ((char *) s + s_size);
	return (0);
}
