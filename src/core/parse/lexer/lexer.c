/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:51:22 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:29:39 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_token(t_lexer *lexer, t_data *data)
{
	if (lexer->token != 0)
		return ;
	if (!white_space(data->line[lexer->index]))
	{
		while (!(lexer->token))
			lexer->token = get_token();
	}
}

int	rediraction_token_possible(t_lexer *lexer, char next)
{
	if (ft_strcmp(lexer->token->content, "<<") == 0)
		lexer->token->type = HEREDOC;
	if (ft_strcmp(lexer->token->content, "<<") == 0
		|| ft_strcmp(lexer->token->content, ">>") == 0
		|| (ft_strcmp(lexer->token->content, "<") == 0
			&& next != '<')
		|| (ft_strcmp(lexer->token->content, ">") == 0
			&& next != '>'))
		return (1);
	return (0);
}

void	close_token(t_lexer *lexer, t_data *data)
{
	char	next;

	next = data->line[lexer->index + 1];
	if (!(lexer->token))
		return ;
	if (lexer->quote_flag)
		return ;
	if ((lexer->token->type != REDIRECTION && (next == '<' || next == '>'))
		|| (lexer->token->type == REDIRECTION
			&& rediraction_token_possible(lexer, next))
		|| (lexer->token->type == PIPE)
		|| (next == '\0' || next == '|')
		|| (lexer->quote_flag == 0 && white_space(next)))
	{
		append(lexer->tokens, lexer->token);
		lexer->token = 0;
	}
}
