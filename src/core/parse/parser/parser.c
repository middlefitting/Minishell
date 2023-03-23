#include "parser.h"

void	simple_cmd_parser(t_cmd *cmd, t_deque *tokens)
{
	t_token	*token;

	token = popleft(tokens);
	if (!cmd->simple_cmd)
	{
		cmd->simple_cmd = init_simple_cmd();
		cmd->simple_cmd->argv = get_deque();
		set_built_in_flag(cmd, token);
		cmd->simple_cmd->file_path = token;
	}
	append(cmd->simple_cmd->argv, token);
}

int	redirect_parser(t_redirect *redirect, t_deque *tokens)
{
	redirect->type = popleft(tokens);
	if (!(tokens->top))
	{
		print_syntax_error("newline");
		return (0);
	}
	if (tokens->top->type == PIPE ||
		tokens->top->type == REDIRECTION ||
		tokens->top->type == HEREDOC)
	{
		print_syntax_error(tokens->top->content);
		return (0);
	}
	redirect->file_name = popleft(tokens);
	return (1);
}

int redirects_parser(t_redirects **redirects, t_deque *tokens)
{
	if (!(*redirects))
	{
		*redirects = init_redirects();
		(*redirects)->redirect = init_redirect();
		return (redirect_parser((*redirects)->redirect, tokens));
	}
	else
		return (redirects_parser(&((*redirects)->redirects), tokens));
}

int cmd_parser(t_pipe *pipe, t_deque *tokens)
{
	t_token *token;
	t_cmd	*cmd;

	cmd = init_cmd();
	pipe->cmd = cmd;
	while (tokens->top != 0 && tokens->top->type != PIPE)
	{
		if (tokens->top->type == WORD)
			simple_cmd_parser(cmd, tokens);
		else if (tokens->top->type == REDIRECTION || tokens->top->type == HEREDOC)
		{
			if (!redirects_parser(&(cmd->redirects), tokens))
				return(0);
		}
	}
	return (1);
}

int	pipe_parser(t_pipe *pipe, t_deque *tokens)
{
	t_token	*token;
	t_pipe *next_pipe;

	if (!(tokens->top) ||
		tokens->top->type == PIPE)
	{
		print_syntax_error("|");
		return (0);
	}
	if (!cmd_parser(pipe, tokens))
		return (0);
	token = popleft(tokens);
	if (!token)
		return (1);
	if (token->type != PIPE)
	{
		print_syntax_error("|");
		return (0);
	}
	next_pipe = init_pipe();
	pipe->pipe = next_pipe;
	free_token(token);
	return (pipe_parser(pipe->pipe, tokens));
}
