#include "parser.h"

t_token	*get_token()
{
	t_token *token;

	token = 0;
	while (!token)
		token = ft_calloc(1, sizeof(t_token));
	while (!(token->content))
		token->content = ft_calloc(1, sizeof(char));
	return token;
}

t_token	*get_env_token()
{
	t_token *token;

	token = 0;
	while (!token)
		token = ft_calloc(1, sizeof(t_token));
	return token;
}
