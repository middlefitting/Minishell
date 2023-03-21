#include "exec.h"

void	mk_num(char *str, int num)
{
	int	i;
	int j;

	i = 0;
	j = 1;
	while (i < 6)
	{
		if (i == 0)
		{
			str[13 + i++] = num / 100000 + '0';
			num %= 100000;
		}
		str[13 + i++] = num / (100000 / (j * 10)) + '0';
		num %= (100000 / (j * 10));
		j *= 10;
	}
}

char	*mk_filename(void)
{
	char	*str;
	int		exist;
	int		i;

	str = ft_strdup ("/tmp/here_doc000000");
	i = 0;
	exist = 0;
	while (exist == 0)
	{
		mk_num (str, i++);
		exist = access (str, F_OK);
	}
	return (str);
}

void	rm_heredoc(void)
{
	char	*str;
	int		exist;
	int		i;

	str = ft_strdup ("/tmp/here_doc000000");
	exist = 0;
	i = 0;
	while (exist == 0)
	{
		mk_num (str, i++);
		exist = access (str, F_OK);
		if (!exist)
			unlink (str);
	}
}