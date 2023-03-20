/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:46:22 by jhwang2           #+#    #+#             */
/*   Updated: 2023/03/19 15:29:43 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	int				fd;
}	t_list;

t_list	*lstnew(int fd);
void	lstfree(t_list **backup);
char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
int		gnl_strlen(const char *str);
char	*gnl_split(t_list **backup);
char	*read_fd(int fd, t_list **backup);
int		gnl_strchr(const char *s, int c);
int	gnl_strchr(const char *s, int c);
int	gnl_strncmp(const char *s1, const char *s2, size_t n);

#endif
