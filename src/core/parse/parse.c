/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: middlefitting <middlefitting@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:53:37 by sechung           #+#    #+#             */
/*   Updated: 2023/03/27 12:41:53 by middlefitti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(t_data *data)
{
	t_lexer	lexer;

	init_lexer(&lexer);
	while (data->line[lexer.index])
	{
		open_token(&lexer, data);
		append_element(&lexer, data);
		close_token(&lexer, data);
		lexer.index = lexer.index + 1;
	}
	data->tokens = lexer.tokens;
	if (data->tokens->size == 0)
		return (0);
	return (1);
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

int	parse(t_data *data)
{
	if (!quote_check(data->line) || !env_parser(data))
	{
		g_exit_status = 258;
		return (0);
	}
	if (!lexer(data))
	{
		g_exit_status = 0;
		return (0);
	}
	if (!parser(data))
	{
		g_exit_status = 258;
		return (0);
	}
	return (1);
}
