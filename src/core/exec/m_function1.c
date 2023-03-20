#include "exec.h"

int	m_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	int				i;

	string1 = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (n && (string1[i] == string2[i]))
	{
		if (string1[i] == '\0' && string2[i] == '\0')
			break ;
		i++;
		n--;
	}
	if (n == 0)
		return (string1[i - 1] - string2[i - 1]);
	return (string1[i] - string2[i]);
}

int	m_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1 == s2)
		return (0);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && s2[i] == 10)
		return (unsigned char) s1[i] - (unsigned char) s2[i] + 10;
	return (unsigned char) s1[i] - (unsigned char) s2[i];
}

void	*m_calloc(size_t count, size_t size)
{
	void	*tmp;
	int		i;

	tmp = malloc(size * count);
	if (tmp == 0)
		return (0);
	i = size * count;
	m_bzero (tmp, i);
	return (tmp);
}

void	m_bzero(void *s, size_t n)
{
	m_memset (s, 0, n);
}

void	*m_memset(void *b, int c, size_t len)
{
	unsigned char	a;
	unsigned char	*tmp;

	a = (unsigned char)c;
	tmp = (unsigned char *)b;
	while (len)
	{
		*tmp = a;
		tmp++;
		len--;
	}
	return (b);
}
