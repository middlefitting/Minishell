#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <dirent.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

enum	e_token_type {
	DEFAULT,
	WORD,
	PIPE,
	REDIRECTION,
	HEREDOC,
	PATH,
}	t_token_type;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
	struct s_token	*pre;
}	t_token;

typedef struct s_deque
{
	t_token		*top;
	t_token		*bottom;
	int			size;
}	t_deque;

typedef struct s_lexer
{
	int		index;
	int		quote_flag;
	int 	token_flag;
	t_deque *tokens;
	t_token *token;
}	t_lexer;

typedef struct s_data
{
	char	*line;
	t_deque	*tokens;
}	t_data;

typedef struct s_redirect
{
	t_token *type;
	t_token *file_name;
}	t_redirect;

typedef struct s_redirects
{
	t_redirect 			*redirect;
	struct s_redirects 	*redirects;
}	t_redirects;

typedef struct s_simple_cmd
{
	t_token	*file_path;
	t_token	*argv[];
}	t_simple_cmd;

typedef struct s_cmd
{
	t_redirects 	*redirects;
	t_simple_cmd	*t_simple_cmd;
}	t_cmd;

typedef struct s_pipe
{
	t_cmd			*cmd;
	struct s_pipe	 *pipe;
}	t_pipe;


t_deque	*get_deque();
void	*append(t_deque *deque, t_token *token);
void	*appendleft(t_deque *deque, t_token *token);
t_token	*pop(t_deque *deque);
t_token	*popleft(t_deque *deque);
t_token	*get_token();
void	free_deque_with_token(t_deque *deque);
void	free_deque(t_deque *deque);
void	free_token(t_token *token);
int	parse(t_data *data);
#endif

