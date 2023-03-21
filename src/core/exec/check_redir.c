# include "exec.h"

extern int	mexit_status;
void	check_redir(t_process *proc)
{
	t_redirects	*redirects;
	char		*content;

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

void	check_infile(t_process * proc, t_token *file, char *content) //ls lllll | wc 테스트필요
{
	char	*str;
	char	buf[BUFFER_SIZE];
	int		fd;

	if (proc->pid == 1 && proc->pipe->cmd->simple_cmd != NULL
		&& proc->pipe->cmd->simple_cmd->built_in_flag && !proc->std_in)
		proc->std_in = dup (STDIN_FILENO);
	if (!ft_strcmp (content, "<<")) // <<만 들어오면 리턴
	{
		rm_heredoc ();
		fd = open (mk_filename(), O_RDWR | O_CREAT, 0644);
		while (1)
		{
			str = get_next_line (STDIN_FILENO);//read (STDIN_FILENO, str, BUFFER_SIZE);//
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
		fd = open (file->content, O_RDONLY | O_CREAT, 0644);
	dup2 (fd, STDIN_FILENO);
	check_file (proc, STDIN_FILENO);
	close (fd);
}

void	check_outfile(t_process *proc, t_token *file, char *content)
{
	int	fd;

	if (proc->pid == 1 && proc->pipe->cmd->simple_cmd != NULL
		&& proc->pipe->cmd->simple_cmd->built_in_flag && !proc->std_out)
		proc->std_out = dup (STDOUT_FILENO);
	if (!ft_strcmp (content, ">>"))
		fd = open (file->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (!ft_strcmp (content, ">"))
		fd = open (file->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
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