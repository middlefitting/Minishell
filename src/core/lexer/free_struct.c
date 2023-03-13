#include "parser.h"

void	free_token(t_token *token)
{
	if (token->content)
		free(token->content);
	free(token);
	return ;
}

void	free_deque(t_deque *deque)
{
	free(deque);
	return ;
}

void	free_deque_with_token(t_deque *deque)
{
	t_token *temp;
	t_token *pre;

	temp = deque->top;
	while (temp)
	{
		pre = temp;
		temp = pre->next;
		free(pre);
	}
	free(deque);
	return ;
}
