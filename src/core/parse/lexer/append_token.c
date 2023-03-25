/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:49:09 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:18:16 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_type(t_lexer *lexer, t_data *data)
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

void	append_token_content(t_lexer *lexer, t_data *data)
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

void	append_element(t_lexer *lexer, t_data *data)
{
	int	next_quote_flag;

	if (lexer->token == 0)
		return ;
	if (lexer->token->type == DEFAULT)
		set_token_type(lexer, data);
	next_quote_flag = renew_quote_flag(lexer->quote_flag,
			data->line[lexer->index]);
	if (next_quote_flag == lexer->quote_flag)
		append_token_content(lexer, data);
	lexer->quote_flag = next_quote_flag;
}
