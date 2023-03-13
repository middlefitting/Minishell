/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: middlefitting <middlefitting@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:56:29 by sechung           #+#    #+#             */
/*   Updated: 2023/03/13 15:45:19 by middlefitti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	result = (void *) malloc(size * count);
	if (result == 0)
		return (0);
	ft_bzero(result, size * count);
	return (result);
}
