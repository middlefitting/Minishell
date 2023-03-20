#include "exec.h"

char	**m_split(char const *s, char c)
{
	char	**return_s;
	char	*tmp;
	int		count_s;
	int		i;

	tmp = (char *)s;
	i = 0;
	count_s = m_str_count (tmp, c);
	return_s = (char **)malloc(sizeof(char *) * (count_s + 1));
	if (return_s == 0 || s == 0)
		return (0);
	while (i < count_s)
	{
		return_s[i] = m_indiv_str (m_str_len(&tmp, c), tmp);
		if (return_s[i] == 0)
		{
			free_all (return_s);
			return (0);
		}
		i++;
	}
	return_s[count_s] = 0;
	return (return_s);
}

int	m_str_count(char *str, char c)
{
	size_t	i;
	int		count;

	if (str == 0)
		return (0);
	i = 0;
	count = 0;
	while (str[i] == c && str[i] != '\0')
		i++;
	while (str[i])
	{
		if (str[i] != c)
		{
			while (str[i] != c && str[i] != '\0')
				i++;
			count++;
		}
		if (str[i] == '\0')
			return (count);
		i++;
	}
	return (count);
}

char	*m_indiv_str(int str_len, char *str)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	tmp1 = (char *)malloc(sizeof(char) * str_len + 1);
	if (tmp1 == 0)
		return (0);
	tmp2 = str - str_len;
	i = 0;
	while (i < str_len)
	{
		tmp1[i] = *tmp2;
		i++;
		tmp2++;
	}
	tmp1[i] = '\0';
	return (tmp1);
}

int	m_str_len(char **str, char c)
{
	int	count;

	count = 0;
	while (**str == c)
		(*str)++;
	while (**str != c && **str != '\0')
	{
		count++;
		(*str)++;
	}
	return (count);
}
