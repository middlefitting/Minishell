# include "exec.h"

extern int	mexit_status;
void	check_redir(t_process *proc)
{
	t_redirects	*redirects;
	char		*content;
	int			std_in;

	redirects = proc->pipe->cmd->redirects;
	std_in = dup (STDIN_FILENO);
	while (redirects != NULL)
	{
		content = redirects->redirect->type->content;
		if (!ft_strcmp (content, "<<") | !ft_strcmp (content, "<"))
			check_infile (proc, redirects->redirect->file_name, content, std_in);
		else if (!ft_strcmp (content, ">>") | !ft_strcmp (content, ">"))
			check_outfile (proc, redirects->redirect->file_name, content);
		redirects = redirects->redirects;
	}
	close (std_in);
}

void	check_infile(t_process * proc, t_token *file, char *content, int std_in) //ls lllll | wc 테스트필요
{
	char	*str;
	int		fd;

	if (!ft_strcmp (content, "<<"))
	{
		rm_heredoc ();
		fd = open (mk_filename(), O_RDWR | O_CREAT, 0644);
		while (1)
		{
			str = get_next_line (std_in);
			if (!ft_strcmp (file->content, str))
				break ;
			write (fd, str, ft_strlen (str));
		}
	}
	else if (!ft_strcmp (content, "<"))
	{
		fd = open (file->content, O_RDONLY | O_CREAT, 0644);
		check_file (proc, STDIN_FILENO);
	}
	if (proc->pid != 1)
		dup2 (fd, STDIN_FILENO);
	close (fd);
}

void	check_outfile(t_process *proc, t_token *file, char *content)
{
	int	fd;

	if (!ft_strcmp (content, ">>"))
		fd = open (O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (!ft_strcmp (content, ">"))
		fd = open (O_WRONLY | O_CREAT, 0644);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
	check_file (proc, STDOUT_FILENO);
}

void	check_file(t_process *proc, int fd)
{
	if (fd < 0)
	{
		write (2, "no such file or directory\n", 26);
		close_fds (proc, 1);
		mexit_status = 1;
		exit (1);
	}
}