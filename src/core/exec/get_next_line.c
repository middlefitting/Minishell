#include "get_next_line.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*tmp;
	int		len_s1;
	int		len_s2;
	int		i;

	i = 0;
	if (s1 == NULL)
		s1 = "";
	len_s1 = gnl_strlen(s1);
	len_s2 = gnl_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (tmp == 0)
		return (0);
	while (i < len_s1)
		tmp[i++] = *s1++;
	i = 0;
	while (i < len_s2)
		tmp[i++ + len_s1] = *s2++;
	tmp[len_s1 + len_s2] = '\0';
	return (tmp);
}

int	gnl_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_split(t_list **backup)
{
	char	*tmp;
	char	*temp;
	int		i;
	int		j;

	j = 0;
	if ((*backup)->content == NULL)
		return (NULL);
	i = gnl_strchr ((*backup)->content, '\n');
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		return (NULL);
	temp = (*backup)->content;
	while (j < i)
		tmp[j++] = *(*backup)->content++;
	tmp[j] = '\0';
	(*backup)->content = gnl_strjoin((*backup)->content, "");
	if ((*backup)->content[0] == '\0')
	{
		free ((*backup)->content);
		(*backup)->content = NULL;
	}
	free (temp);
	return (tmp);
}

char	*read_fd(int fd, t_list **backup)
{
	char	tmp[BUFFER_SIZE + 1];
	char	*tmpptr;
	int		count;
	int		i;

	if (read (fd, 0, 0) == -1)
		return (NULL);
	while (1)
	{
		i = 0;
		count = read (fd, tmp, BUFFER_SIZE);
		if (count == 0)
			break ;
		tmp[count] = '\0';
		tmpptr = (*backup)->content;
		(*backup)->content = gnl_strjoin ((*backup)->content, tmp);
		if (tmpptr != NULL)
			free (tmpptr);
		while (tmp[i] != '\n' && tmp[i] != '\0')
			i++;
		if (tmp[i] == '\n')
			break ;
	}
	tmpptr = gnl_split (backup);
	return (tmpptr);
}

char	*get_next_line(int fd)
{
	static t_list	*backup;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (backup == NULL)
	{
		backup = lstnew (fd);
		if (backup == NULL)
			return (NULL);
	}
	line = read_fd (fd, &backup);
	if (line == NULL)
	{
		lstfree (&backup);
		backup = NULL;
	}
	return (line);
}