#include "parser.h"

t_deque	*get_deque()
{
	t_deque *deque;

	deque = 0;
	while(!deque)
		deque = ft_calloc(1, sizeof(t_deque));
	return deque;
}

void	append(t_deque *deque, t_token *token)
{
	if (deque->size == 0)
	{
		deque->top = token;
		deque->bottom = token;
		token->pre = 0;
	}
	else
	{
		deque->bottom->next = token;
		token->pre = deque->bottom;
		deque->bottom = token;
	}
	token->next = 0;
	// deque->size = deque->size += 1;
	deque->size += 1;
}

void	appendleft(t_deque *deque, t_token *token)
{
	if (deque->size == 0)
	{
		deque->top = token;
		deque->bottom = token;
		token->next = 0;
	}
	else
	{
		deque->top->pre = token;
		token->next = deque->top;
		deque->top = token;
	}
	token->pre = 0;
	// deque->size = deque->size += 1;
	deque->size += 1;
}

t_token	*pop(t_deque *deque)
{
	t_token *result;

	result = deque->bottom;
	if (deque->size == 0)
		return (0);
	else if (deque->size == 1)
	{
		deque->top = 0;
		deque->bottom = 0;
	}
	else
	{
		deque->bottom = deque->bottom->pre;
		deque->bottom->next = 0;
	}
	result->next = 0;
	result->pre = 0;
	// deque->size = deque->size -= 1;
	deque->size -= 1;
	return (result);
}

t_token	*popleft(t_deque *deque)
{
	t_token *result;

	result = deque->top;
	if (deque->size == 0)
		return (0);
	else if (deque->size == 1)
	{
		deque->top = 0;
		deque->bottom = 0;
	}
	else
	{
		deque->top = deque->top->next;
		deque->top->pre = 0;
	}
	result->next = 0;
	result->pre = 0;
	// deque->size = deque->size -= 1;
	deque->size -= 1;
	return (result);
}
