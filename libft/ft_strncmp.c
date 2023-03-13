/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: middlefitting <middlefitting@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:04:52 by sechung           #+#    #+#             */
/*   Updated: 2023/03/13 19:16:51 by middlefitti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	diff = 0;
	if (s1 == s2)
		return (0);
	while (i < n && s1[i] && s1[i] == s2[i])
		i++;
	if (i < n)
		diff = (unsigned char) s1[i] - (unsigned char) s2[i];
	if (diff != 0)
		return (diff);
	return (0);
}
