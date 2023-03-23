
#include "parser.h"

void print_parse_error(char *msg)
{
	ft_putstr_fd("minishell: parse error by ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void print_syntax_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
}
