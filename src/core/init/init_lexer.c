#include "parser.h"

void init_lexer(t_lexer *lexer)
{
	lexer->index = 0;
	lexer->quote_flag = 0;
	lexer->token = 0;
	lexer->token_flag = 0;
	lexer->tokens = 0;
	lexer->tokens = get_deque();
}
