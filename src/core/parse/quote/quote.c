#include "parser.h"

int	renew_quote_flag(int flag, char c)
{
	if (flag == 0)
	{
		if (c == '\'')
			return (1);
		else if (c == '\"')
			return (2);
	}
	else if (flag == 1)
	{
		if (c == '\'')
			return (0);
	}
	else if (flag == 2)
	{
		if (c == '\"')
			return (0);
	}
	return (flag);
}

int quote_check(char *line)
{
	int	ind;
	int	flag;

	ind = 0;
	flag = 0;
	while (line[ind])
	{
		if (line[ind] == '\'' || line[ind] == '\"')
			flag = renew_quote_flag(flag, line[ind]);
		ind++;
	}
	if (flag == 0)
		return (1);
	else if (flag == 1)
		print_parse_error("unclosed quote");
	else if (flag == 2)
		print_parse_error("unclosed dquote");
	return (0);
}
