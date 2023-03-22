#include "exec.h"

void	mk_num(char *str, int num)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < 6)
	{
		if (i == 0)
		{
			str[13 + i++] = num / 100000 + '0';
			num %= 100000;
		}
		str[13 + i++] = num / (100000 / (j * 10)) + '0';
		num %= (100000 / (j * 10));
		j *= 10;
	}
}

char	*mk_filename(void)
{
	char	*str;
	int		exist;
	int		i;

	str = ft_strdup ("/tmp/here_doc000000");
	i = 0;
	exist = 0;
	while (exist == 0)
	{
		mk_num (str, i++);
		exist = access (str, F_OK);
	}
	return (str);
}

void	rm_heredoc(void)
{
	char	*str;
	int		exist;
	int		i;

	str = ft_strdup ("/tmp/here_doc000000");
	exist = 0;
	i = 0;
	while (exist == 0)
	{
		mk_num (str, i++);
		exist = access (str, F_OK);
		if (!exist)
			unlink (str);
	}
}

void	check_heredoc(t_process *proc, t_redirects *redirects)
{
	char	*str;
	int		fd;

	while (redirects)
	{
		if (!ft_strcmp (redirects->redirect->type->content, "<<"))
		{
			fd = open (proc->heredoc_file[proc->fd_idx],
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
			while (1)
			{
				str = readline ("> ");
				if (!ft_strcmp (redirects->redirect->file_name->content, str))
				{
					free (str);
					close (fd);
					break ;
				}
				write (fd, str, ft_strlen (str));
				write (fd, "\n", 1);
				free (str);
			}
		}
		redirects = redirects->redirects;
	}
}

void	mk_heredoc(t_process *proc)
{
	t_pipe	*pipe;

	pipe = proc->pipe;
	while (pipe)
	{
		proc->heredoc_file[proc->fd_idx] = mk_filename();
		if (pipe->cmd->redirects)
			check_heredoc (proc, pipe->cmd->redirects);
		proc->fd_idx++;
		pipe = pipe->pipe;
	}
}
