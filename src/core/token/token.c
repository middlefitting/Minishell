/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:54:52 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:19:12 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_token(void)
{
	t_token	*token;

	token = 0;
	while (!token)
		token = ft_calloc(1, sizeof(t_token));
	while (!(token->content))
		token->content = ft_calloc(1, sizeof(char));
	return (token);
}

t_token	*get_env_token(void)
{
	t_token	*token;

	token = 0;
	while (!token)
		token = ft_calloc(1, sizeof(t_token));
	return (token);
}
