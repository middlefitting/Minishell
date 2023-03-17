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
		free_token(pre);
	}
	free(deque);
	return ;
}

void	free_redirect(t_redirect *redirect)
{
	if (redirect->type)
		free_token(redirect->type);
	if (redirect->file_name)
		free(redirect->file_name);
	free(redirect);
}

void	free_redirects(t_redirects *redirects)
{
	if (redirects->redirect)
		free_redirect(redirects->redirect);
	if (redirects->redirects)
		free_redirects(redirects->redirects);
	free(redirects);
}

void	free_simple_cmd(t_simple_cmd *simple_cmd)
{
	if (simple_cmd->argv)
		free_deque_with_token(simple_cmd->argv);
	free(simple_cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->simple_cmd)
		free_simple_cmd(cmd->simple_cmd);
	if (cmd->redirects)
		free_redirects(cmd->redirects);
	free(cmd);
}

void	free_pipe(t_pipe *pipe)
{
	if (pipe->cmd)
		free_cmd(pipe->cmd);
	if (pipe->pipe)
		free_pipe(pipe->pipe);
	free(pipe);
}
