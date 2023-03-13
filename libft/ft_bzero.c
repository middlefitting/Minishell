/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:18:15 by sechung           #+#    #+#             */
/*   Updated: 2022/07/06 16:45:00 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *dest, size_t size)
{
	size_t			i;
	unsigned char	*c_dest;

	i = 0;
	c_dest = (unsigned char *) dest;
	while (i < size)
	{
		c_dest[i] = 0;
		i++;
	}
}
