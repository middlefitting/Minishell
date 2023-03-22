#include "exec.h"

void	path_error(char *path)
{
	struct stat	file;

	if (stat(path, &file) == ERROR)
		if (errno == ENOENT)
			print_error ("cd", path, 0);
	if ((file.st_mode & S_IFMT) != S_IFDIR)
		print_error ("cd", path, 3);
}

void	print_error(const char *cmd, char *option, int flags)
{
	char	*tmp;
	char	*str;

	str = ft_strdup (cmd);
	tmp = str;
	str = m_strjoin ("minishell: ", str);
	free (tmp);
	if (option)
	{
		tmp = str;
		str = m_strjoin (str, ": ");
		free (tmp);
		tmp = str;
		str = m_strjoin (str, option);
		free (tmp);
	}
	print_errortype (str, flags);
}

void	print_errortype(char *str, int flags)
{
	char	*tmp;

	tmp = str;
	if (flags == 0)
		str = m_strjoin (str, ": No such file or directory\n");
	else if (flags == 1)
		str = m_strjoin (str, ": command not found\n");
	else if (flags == 2)
		str = m_strjoin (str, ": not a valid identifier\n");
	else if (flags == 3)
		str = m_strjoin (str, ": Not a directory\n");
	free (tmp);
	write (2, str, ft_strlen (str));
	free (str);
}
