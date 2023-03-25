/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_builtins3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:37:14 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:17:41 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_patherror(char *path, char *home, int opt_flag)
{
	int	error;
	int	i;

	error = 0;
	i = 0;
	if (path == NULL && home == NULL)
		error = 1;
	else
	{
		error = chdir (path);
		if (error != 1 && opt_flag == 2)
		{
			while (path[i])
				write (1, &path[i++], 1);
			write (1, "\n", 1);
		}
	}
	if (error)
		path_error (path, home, opt_flag);
	else
		g_exit_status = 0;
	return ;
}

void	m_pwd(t_process *proc, int flag)
{
	char	*path;
	int		i;

	i = 0;
	path = getcwd (NULL, 0);
	if (path == NULL)
	{
		free (path);
		g_exit_status = 1;
		mexit (flag, g_exit_status);
	}
	while (path[i] != '\0')
		write (STDOUT_FILENO, &path[i++], 1);
	write (STDOUT_FILENO, "\n", 1);
	free (path);
	if (proc->num_of_pipe == 0)
		recover_std (proc);
	mexit (flag, g_exit_status);
}
