/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:11:05 by sechung           #+#    #+#             */
/*   Updated: 2022/07/06 22:31:52 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	size_t	temp;
	char	*result;

	temp = 0;
	if (!s || !f)
		return (0);
	size = ft_strlen(s);
	result = malloc(sizeof(char) * size + 1);
	if (!result)
		return (0);
	result[size] = 0;
	while (temp < size)
	{
		result[temp] = f((unsigned int) temp, s[temp]);
		temp += 1;
	}
	return (result);
}
