/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:48:23 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:18:08 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexer(t_lexer *lexer)
{
	lexer->index = 0;
	lexer->quote_flag = 0;
	lexer->token = 0;
	lexer->token_flag = 0;
	lexer->tokens = 0;
	lexer->tokens = get_deque();
}
