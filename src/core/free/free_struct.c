/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:48:03 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:18:00 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	if (token->content)
		free(token->content);
	if (token->name)
		free(token->name);
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
	t_token	*temp;

	temp = popleft(deque);
	while (temp)
	{
		free_token(temp);
		temp = popleft(deque);
	}
	free(deque);
	return ;
}

void	free_data(t_data *data)
{
	if (data->tree)
		free_pipe(data->tree);
	if (data->tokens)
		free_deque_with_token(data->tokens);
	if (data->line)
		free (data->line);
	data->line = 0;
	data->tokens = 0;
	data->tree = 0;
}
