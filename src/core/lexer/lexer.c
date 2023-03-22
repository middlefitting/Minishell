#include "parser.h"
#include "exec.h"

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

// int pipe_check(char *line)
// {
// 	int flag;
// 	int ind;

// 	ind = 0;
// 	flag = 0;
// 	while (line[ind])
// 	{
// 		flag = (line[ind] == '|');
// 		if (flag && (line[ind + 1] == '\0'))
// 		{
// 			print_syntax_error("'newline'");
// 			return(0);
// 		}
// 		else if (flag && (line[ind + 1] == '|'))
// 		{
// 			print_syntax_error("'|'");
// 			return(0);
// 		}
// 		ind++;
// 	}
// 	return (0);
// }

// int rediraction_flag_parser(int a, int b, char c)
// {
// 	if (c == '>')
// 		return (a);
// 	else if (c == '<')
// 		return (b);
// 	else
// 		return (0);
// }

// int	renew_rediraction_flag(int flag, char c)
// {
// 	// [1 >] [2 <] [3 >>] [4 <<]
// 	if (flag == 1)
// 		return (rediraction_flag_parser(3, 2, c));
// 	else if (flag == 2)
// 		return (rediraction_flag_parser(1, 4, c));
// 	else
// 		return (rediraction_flag_parser(1, 2, c));
// }

// int rediraction_check(char *line)
// {
// 	int flag;
// 	int ind;

// 	ind = 0;
// 	flag = 0;
// 	while (line[ind])
// 	{
// 		flag = renew_rediraction_flag(flag, line[ind]);
// 		if (flag && (line[ind + 1] == '\0'))
// 			print_syntax_error("'newline'");
// 		if (flag && (line[ind + 1] == '|'))
// 			print_syntax_error("'|'");
// 		ind++;
// 	}
// 	return (0);
// }

void init_lexer(t_lexer *lexer)
{
	lexer->index = 0;
	lexer->quote_flag = 0;
	lexer->token = 0;
	lexer->token_flag = 0;
	lexer->tokens = 0;
	lexer->tokens = get_deque();
}
int	white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

// ls| ls > ''a
void open_token(t_lexer *lexer, t_data *data)
{
	if (lexer->token != 0)
		return;
	if (!white_space(data->line[lexer->index]))
	{
		while (!(lexer->token))
			lexer->token = get_token();
	}
}

void set_token_type(t_lexer *lexer, t_data *data)
{
	char	c;

	c = data->line[lexer->index];
	if (c == '|')
		lexer->token->type = PIPE;
	else if (c == '>' || c == '<')
		lexer->token->type = REDIRECTION;
	else
		lexer->token->type = WORD;
}

void append_token_content(t_lexer *lexer, t_data *data)
{
	char	*renew_content;
	char	*temp;

	temp = 0;
	renew_content = 0;
	while (!temp)
		temp = calloc(2, sizeof(char));
	temp[0] = data->line[lexer->index];
	while (!renew_content)
		renew_content = ft_strjoin(lexer->token->content, temp);
	free(temp);
	free(lexer->token->content);
	lexer->token->content = renew_content;
}

void append_element(t_lexer *lexer, t_data *data)
{
	int	next_quote_flag;

	if (lexer->token == 0)
		return;
	if (lexer->token->type == DEFAULT)
		set_token_type(lexer, data);
	next_quote_flag = renew_quote_flag(lexer->quote_flag, data->line[lexer->index]);
	if (next_quote_flag == lexer->quote_flag)
		append_token_content(lexer, data);
	lexer->quote_flag = next_quote_flag;
}

int	rediraction_token_possible(t_lexer *lexer, char next)
{
	if (ft_strcmp(lexer->token->content, "<<") == 0)
		lexer->token->type = HEREDOC;
	if (ft_strcmp(lexer->token->content, "<<") == 0 ||
		ft_strcmp(lexer->token->content, ">>") == 0 ||
		ft_strcmp(lexer->token->content, "<") == 0 && next != '<' ||
		ft_strcmp(lexer->token->content, ">") == 0 && next != '>')
		return (1);
	return (0);
}

void	close_token(t_lexer *lexer, t_data *data)
{
	char next;

	next = data->line[lexer->index + 1];
	if (!(lexer->token))
		return ;
	if (lexer->quote_flag)
		return ;
	// 널이거나 파이프라면 무조건 토큰 닫기
	// quote 플래그가 0인데 whitespace 만나면 토큰 닫기
	// 토큰타입이 리다이렉션이 아니고 < > 만나면 토큰 닫기
	// 토큰타입이 리다이렉션이고 << >> 이라면 토큰 닫기
	// 토큰타입이 pipe이면 토큰 닫기
	if ((lexer->token->type != REDIRECTION && (next == '<' || next == '>')) ||
		(lexer->token->type == REDIRECTION && rediraction_token_possible(lexer, next)) ||
		(lexer->token->type == PIPE) ||
		(next == '\0' || next == '|') ||
		(lexer->quote_flag == 0 && white_space(next)))
	{
		append(lexer->tokens, lexer->token);
		lexer->token = 0;
	}
}

int	lexer(t_data *data)
{
	t_lexer lexer;
	init_lexer(&lexer);
	while (data->line[lexer.index])
	{
		open_token(&lexer, data);
		append_element(&lexer, data);
		close_token(&lexer, data);
		lexer.index = lexer.index + 1;
	}
	//테스트용 출력부///////////////////////////////////////////
	t_token *token =lexer.tokens->top;
	while (token)
	{
		printf("[%s] %d\n", token->content, token->type);
		token = token->next;
	}
	////////////////////////////////////////////////////////
	data->tokens = lexer.tokens;
	if (data->tokens->size == 0)
		return (0);
	return(1);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////parser//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

t_pipe *init_pipe()
{
	t_pipe	*pipe;

	pipe = 0;
	while (!pipe)
		pipe = ft_calloc(1, sizeof(t_pipe));
	return (pipe);
}

t_cmd *init_cmd()
{
	t_cmd	*cmd;

	cmd = 0;
	while (!cmd)
		cmd = ft_calloc(1, sizeof(t_cmd));
	return (cmd);
}

t_simple_cmd *init_simple_cmd()
{
	t_simple_cmd	*simple_cmd;

	simple_cmd = 0;
	while (!simple_cmd)
		simple_cmd = ft_calloc(1, sizeof(t_simple_cmd));
	return (simple_cmd);
}

t_redirects	*init_redirects()
{
	t_redirects	*redirects;

	redirects = 0;
	while(!redirects)
		redirects = ft_calloc(1, sizeof(t_redirects));
	return (redirects);
}

t_redirect	*init_redirect()
{
	t_redirect	*redirect;

	redirect = 0;
	while(!redirect)
		redirect = ft_calloc(1, sizeof(t_redirect));
	return (redirect);
}

void	set_built_in_flag(t_cmd *cmd, t_token *token)
{
	if (ft_strcmp(token->content, "echo") == 0 ||
		ft_strcmp(token->content, "cd") == 0 ||
		ft_strcmp(token->content, "pwd") == 0 ||
		ft_strcmp(token->content, "export") == 0 ||
		ft_strcmp(token->content, "unset") == 0 ||
		ft_strcmp(token->content, "env") == 0 ||
		ft_strcmp(token->content, "exit") == 0)
		cmd->simple_cmd->built_in_flag = 1;
	else
		cmd->simple_cmd->built_in_flag = 0;
}

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

int	parser(t_data *data)
{
	t_pipe	*tree;

	tree = init_pipe();
	data->tree = tree;
	if (!(data->tokens->top))
		return (1);
	if (!pipe_parser(tree, data->tokens))
		return (0);
	return (1);
}

/////////////////////////////////////////////////////////////
int	parse(t_data *data)
{
	if (quote_check(data->line) &&
		env_parser(data) &&
		lexer(data) &&
		parser(data))
		return (1);
	g_exit_status = 258;
	return (0);
}

////////////////////////////////////////////////////////////
int	get_pipe_size(t_pipe *pipe)
{
	int		result;
	t_pipe	*next;

	result = 0;
	next = pipe->pipe;
	while (next)
	{
		result++;
		next = next->pipe;
	}
	return (result);
}
