#include "exec.h"

void	check_redir(t_process *proc)
{
	t_redirects	*redirects;
	char		*content;

	redirects = proc->pipe->cmd->redirects;
	while (redirects != NULL)
	{
		content = redirects->redirect->type->content;
		if (!ft_strcmp (content, "<<") || !ft_strcmp (content, "<"))
			check_infile (proc, redirects,
				redirects->redirect->file_name, content);
		else if (!ft_strcmp (content, ">>") || !ft_strcmp (content, ">"))
			check_outfile (proc, redirects->redirect->file_name, content);
		redirects = redirects->redirects;
	}
}

void	check_infile(t_process *proc, t_redirects *redirects,
	t_token *file, char *content)
{
	char	*str;
	int		fd;

	if (!ft_strcmp (content, "<<"))
	{
		fd = open (proc->heredoc_file[proc->cmd - 2], O_RDONLY);
		dup2 (fd, STDIN_FILENO);
		return ;
	}
	else if (!ft_strcmp (content, "<"))
		fd = open (file->content, O_RDONLY);
	check_file (proc, redirects, fd);
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
	check_file (proc, 0, fd);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
}

void	check_file(t_process *proc, t_redirects *redirects, int fd)
{
	if (fd < 0)
	{
		print_error (redirects->redirect->file_name->content, 0, 0);
		close_fds (proc, 1);
		g_exit_status = 1;
		if (proc->pid != 1)
			exit (1);
	}
}
