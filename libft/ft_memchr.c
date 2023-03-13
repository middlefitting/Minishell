/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:43:26 by sechung           #+#    #+#             */
/*   Updated: 2022/07/08 10:02:45 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *dest, int ch, size_t size)
{
	unsigned char	*unc_dest;
	unsigned char	unc_ch;
	size_t			i;

	unc_dest = (unsigned char *) dest;
	unc_ch = (unsigned char) ch;
	i = 0;
	while (size--)
	{
		if (unc_dest[i] == unc_ch)
			return ((void *) &unc_dest[i]);
		i++;
	}
	return (0);
}
