/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:20:53 by sechung           #+#    #+#             */
/*   Updated: 2022/07/07 21:42:30 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	equal_check(const char *haystack, const char *needle)
{
	size_t	i;

	i = 0;
	while (needle[i] != 0 && haystack[i] == needle[i])
		i++;
	if (needle[i] == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	size_needle;

	i = 0;
	if (haystack == needle)
		return ((char *) haystack);
	if (*needle == 0)
		return ((char *) haystack);
	size_needle = ft_strlen(needle);
	while (haystack[i] != 0 && i + size_needle <= len)
	{
		if (equal_check(haystack + i, needle))
			return ((char *) haystack + i);
		i++;
	}
	return (0);
}
