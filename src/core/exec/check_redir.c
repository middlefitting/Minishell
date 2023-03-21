# include "exec.h"

extern int	mexit_status;
void	check_redir(t_process *proc)
{
	t_redirects	*redirects;
	char		*content;

	printf ("%d\n", proc->cmd);
	if (!proc->std_in)
		proc->std_in = dup (STDIN_FILENO);
	if (!proc->std_out)
		proc->std_out = dup (STDOUT_FILENO);
	redirects = proc->pipe->cmd->redirects;
	while (redirects != NULL)
	{
		content = redirects->redirect->type->content;
		if (!ft_strcmp (content, "<<") || !ft_strcmp (content, "<"))
			check_infile (proc, redirects->redirect->file_name, content);
		else if (!ft_strcmp (content, ">>") || !ft_strcmp (content, ">"))
			check_outfile (proc, redirects->redirect->file_name, content);
		redirects = redirects->redirects;
	}
}

void	check_infile(t_process * proc, t_token *file, char *content)
{
	char	*str;
	char	buf[BUFFER_SIZE];
	int		fd;

	if (!ft_strcmp (content, "<<"))
	{
		//rm_heredoc ();
		fd = open (mk_filename(), O_RDWR | O_CREAT, 0644);
		while (1)
		{
			str = get_next_line (proc->std_in);
			str[ft_strlen(str) - 1] = '\0';
			if (!ft_strcmp (file->content, str))
			{
				free (str);
				break ;
			}
			write (fd, str, ft_strlen (str));
			write (fd, "\n", 1);
			free (str);
		}
	}
	else if (!ft_strcmp (content, "<"))
		fd = open (file->content, O_RDONLY);
	check_file (proc, fd);
	dup2 (fd, STDIN_FILENO);
	close (fd);
}

void	check_outfile(t_process *proc, t_token *file, char *content)
{
	int	fd;

	if (!ft_strcmp (content, ">>"))
		fd = open (file->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (!ft_strcmp (content, ">"))
		fd = open (file->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	check_file (proc, fd);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
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