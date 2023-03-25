/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_function2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:38:16 by sechung           #+#    #+#             */
/*   Updated: 2023/03/25 13:48:19 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*m_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == 0 || s2 == 0)
		return (0);
	len_s1 = m_strlen(s1);
	len_s2 = m_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (tmp == 0)
		return (0);
	tmp[0] = '\0';
	m_strlcat(tmp, s1, len_s1 + 1);
	m_strlcat(tmp, s2, len_s1 + len_s2 + 1);
	tmp[len_s1 + len_s2] = '\0';
	return (tmp);
}

size_t	m_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	m_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	len_dns;
	size_t	size;

	len_src = 0;
	len_dst = 0;
	while (src[len_src] != '\0')
		len_src++;
	while (dst[len_dst] != '\0')
		len_dst++;
	len_dns = len_dst + len_src;
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	size = dstsize - len_dst - 1;
	while (*src != '\0' && size > 0)
	{
		dst[len_dst] = *src;
		src++;
		len_dst++;
		size--;
	}
	dst[len_dst] = '\0';
	return (len_dns);
}

int	write_str(char *content, int fd)
{
	char	*str;

	while (1)
	{
		str = readline ("> ");
		if (!str)
		{
			free(str);
			close(fd);
			g_exit_status = 0;
			return (1);
		}
		if (!ft_strcmp (content, str))
		{
			free (str);
			close (fd);
			g_exit_status = 0;
			return (0);
		}
		write (fd, str, ft_strlen (str));
		write (fd, "\n", 1);
		free (str);
	}
}

void	fork_error(void)
{
	if (errno == EAGAIN)
		write (1, "minishell: fork: Resource temporarily unavailable\n", 50);
	while (wait(NULL) != -1)
		;
	g_exit_status = 1;
}
