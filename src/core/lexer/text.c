#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

size_t	ft_strlen(const char *str)
{
	size_t	result;

	result = 0;
	while (str[result] != 0)
		result++;
	return (result);
}

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t	i;
	char	*c_dest;
	char	*c_src;

	if (!dest)
		(void)(*((char *) dest));
	if (!src)
		(void)(*((char *) src));
	if (dest == src)
		return (dest);
	c_dest = (char *) dest;
	c_src = (char *) src;
	i = 0;
	while (i < size)
	{
		c_dest[i] = c_src[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size_s1;
	size_t	size_s2;
	char	*dest;

	if (s1 == 0 || s2 == 0)
		return (0);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	dest = malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (dest == 0)
		return (0);
	dest[size_s1 + size_s2] = 0;
	ft_memcpy(dest, s1, size_s1);
	ft_memcpy(dest + size_s1, s2, size_s2);
	return (dest);
}

int main(void)
{
	char *result;
	char *s = "dd";
	char c = 'j';
	char *ss = 0;

	ss = malloc(sizeof(char) * 2);

	ss[0] = 'c';
	ss[1] = 0;
	ss[2] = 'c';
	result = ft_strjoin(s, s);
	result = ft_strjoin(result, ss);
	result = ft_strjoin(result, &c);
	result = ft_strjoin(result, &c);
	write(1, result, 6);
	return(0);
}
