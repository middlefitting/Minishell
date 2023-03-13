/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:19:39 by sechung           #+#    #+#             */
/*   Updated: 2022/07/07 15:10:35 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	c_c;
	size_t	i;

	i = 0;
	c_c = (char) c;
	while (s[i] != c_c && s[i] != 0)
		i++;
	if (s[i] == c_c)
		return ((char *) s + i);
	return (0);
}
