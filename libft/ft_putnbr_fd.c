/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:54:22 by sechung           #+#    #+#             */
/*   Updated: 2022/07/07 21:59:14 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	result;
	int		temp;

	temp = n;
	if (temp == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (temp < 0)
	{
		write(fd, "-", 1);
		temp *= -1;
	}
	if (temp >= 10)
		ft_putnbr_fd(temp / 10, fd);
	result = temp % 10 + '0';
	write(fd, &result, 1);
}
