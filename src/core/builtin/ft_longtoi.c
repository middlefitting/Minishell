#include "minishell.h"

void	init_longtoi(unsigned long long *result, int *sign, int *len, int *start)
{
	*result = 0;
	*sign = 1;
	*len = 0;
	*start = 0;
}

void	white_space_pass(const char *str, size_t *i)
{
	while (white_space(str[*i]))
		*i = *i + 1;
}

void	sign_pass(const char *str, size_t *i, int *sign)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = *sign * (-1);
		*i = *i + 1;
	}
}

void	renew_len(char c, int *start, int *len, int *flag)
{
	if (c != '0')
		*start = 1;
	if (*start)
		*len = *len + 1;
	if (*len >= 20)
		*flag = 0;
}

int	ft_longtoi(const char *str, int *flag)
{
	size_t				i;
	unsigned long long	result;
	int					sign;
	int					len;
	int					start;

	i = 0;
	init_longtoi(&result, &sign, &len, &start);
	white_space_pass(str, &i);
	sign_pass(str, &i, &sign);
	if (str[i] == 0 || white_space(str[i]))
		*flag = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		renew_len(str[i], &start, &len, flag);
		result = result * 10 + str[i] - '0';
		if (((result > 9223372036854775807ULL) && (sign == 1))
			|| ((result > 9223372036854775808ULL) && (sign == -1)))
			*flag = 0;
		i++;
	}
	white_space_pass(str, &i);
	if (str[i] != 0)
		*flag = 0;
	return (((int) result) * sign);
}
