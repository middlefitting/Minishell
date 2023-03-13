/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:35:17 by sechung           #+#    #+#             */
/*   Updated: 2022/07/06 21:23:28 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_length(int n)
{
	size_t		result;
	long long	temp;

	result = 0;
	temp = (long long) n;
	if (n < 0)
	{
		result = 1;
		temp *= -1;
	}
	if (n == 0)
		result = 1;
	while (temp > 0)
	{
		temp /= 10;
		result += 1;
	}
	return (result);
}

void	initialize(char *dest, int n, int size)
{
	long long	temp;

	temp = (long long) n;
	if (temp < 0)
	{
		*dest = '-';
		temp *= -1;
	}
	if (temp == 0)
		dest[--size] = '0';
	while (temp != 0)
	{
		dest[--size] = temp % 10 + '0';
		temp /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	size;

	size = ft_length(n);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (0);
	result[size] = '\0';
	initialize(result, n, size);
	return (result);
}
