/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:48:36 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:18:13 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*init_pipe(void)
{
	t_pipe	*pipe;

	pipe = 0;
	while (!pipe)
		pipe = ft_calloc(1, sizeof(t_pipe));
	return (pipe);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = 0;
	while (!cmd)
		cmd = ft_calloc(1, sizeof(t_cmd));
	return (cmd);
}

t_simple_cmd	*init_simple_cmd(void)
{
	t_simple_cmd	*simple_cmd;

	simple_cmd = 0;
	while (!simple_cmd)
		simple_cmd = ft_calloc(1, sizeof(t_simple_cmd));
	return (simple_cmd);
}

t_redirects	*init_redirects(void)
{
	t_redirects	*redirects;

	redirects = 0;
	while (!redirects)
		redirects = ft_calloc(1, sizeof(t_redirects));
	return (redirects);
}

t_redirect	*init_redirect(void)
{
	t_redirect	*redirect;

	redirect = 0;
	while (!redirect)
		redirect = ft_calloc(1, sizeof(t_redirect));
	return (redirect);
}
