/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:20:34 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:16:58 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_simple_cmd *simple_cmd, t_deque *envs)
{
	char	*name;
	t_token	*temp;
	int		flag;

	flag = 0;
	if (simple_cmd->argv->size == 1)
	{
		g_exit_status = flag;
		return ;
	}
	temp = simple_cmd->argv->top->next;
	while (temp)
	{
		name = get_env_name(temp->content);
		if (env_name_check(name) == 1)
			remove_env(envs, name);
		if (env_name_check(name) == 0)
		{
			flag = 1;
			print_error("unset", temp->content, 2);
		}
		free(name);
		temp = temp->next;
	}
	g_exit_status = flag;
}
