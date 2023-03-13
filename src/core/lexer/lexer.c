#include "parser.h"

void print_parse_error(char *msg)
{
	ft_putstr_fd("minishell: parse error by ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void print_syntax_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
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
	while (!(lexer->tokens))
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
	// 널이거나 파이프라면 무조건 토큰 닫기
	// quote 플래그가 0인데 whitespace 만나면 토큰 닫기
	// 토큰타입이 리다이렉션이 아니고 < > 만나면 토큰 닫기
	// 토큰타입이 리다이렉션이고 << >> 이라면 토큰 닫기
	// 토큰타입이 pipe이면 토큰 닫기
	if ((next == '\0' || next == '|') ||
		(lexer->quote_flag == 0 && white_space(next)) ||
		(lexer->token->type != REDIRECTION && (next == '<' || next == '>')) ||
		(lexer->token->type == REDIRECTION && rediraction_token_possible(lexer, next)) ||
		(lexer->token->type == PIPE))
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
		pipe = calloc(1, sizeof(t_pipe));
	return (pipe);
}

int	pipe_parser(t_pipe *pipe, t_deque *deque)
{
	t_token	*token;

	token = popleft(deque);
	if (!token)
		return (1);
	if (token->type == PIPE)
	{
		print_syntax_error("|");
		appendleft(deque, token);
		return (0);
	}
	return(1);
}

int	parser(t_data *data)
{
	t_pipe	*tree;

	tree = init_pipe();
	pipe_parser(tree, data->tokens);
}

/////////////////////////////////////////////////////////////
int	parse(t_data *data)
{
	return (
		quote_check(data->line) &&
		lexer(data) &&
		parser(data)
	);
}
