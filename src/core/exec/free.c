/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:52:25 by jhwang2           #+#    #+#             */
/*   Updated: 2023/03/22 13:49:43 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_proc(t_process *proc)
{
	int	i;

	i = 0;
	if (proc->fds)
	{
		while (i < proc->num_of_pipe)
			free (proc->fds[i++]);
		free (proc->fds);
	}
	free_heredoc (proc);
	free (proc);
}

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		free (str[i]);
		i++;
	}
	free (str);
}

void	free_heredoc(t_process *proc)
{
	int	i;

	i = 0;
	while (i <= proc->num_of_pipe)
		free (proc->heredoc_file[i++]);
	free (proc->heredoc_file);
}
