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
	char			*name;
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
	t_deque	*argv;
	int		built_in_flag;
}	t_simple_cmd;

typedef struct s_cmd
{
	t_redirects 	*redirects;
	t_simple_cmd	*simple_cmd;
}	t_cmd;

typedef struct s_pipe
{
	t_cmd			*cmd;
	struct s_pipe	 *pipe;
}	t_pipe;


typedef struct s_data
{
	char	*line;
	t_deque	*tokens;
	t_deque	*envs;
	t_pipe	*tree;
}	t_data;

t_deque	*get_deque();
void	append(t_deque *deque, t_token *token);
void	appendleft(t_deque *deque, t_token *token);
t_token	*pop(t_deque *deque);
t_token	*popleft(t_deque *deque);
t_token	*get_token();
void	free_deque_with_token(t_deque *deque);
void	free_deque(t_deque *deque);
void	free_token(t_token *token);
int		parse(t_data *data);
void	free_pipe(t_pipe *pipe);


void	env_init(t_data *data, char **envp);
t_token	*get_env_token();
char	*get_env(t_deque *envs, char *name);
void	env_append(t_deque *envs, char *raw);
int		white_space(char c);
int		env_parser(t_data *data);
int		renew_quote_flag(int flag, char c);
char	*join_line(char *dest, char *s);
void	remove_env(t_deque *envs, char *name);
char	**get_envs_pointer(t_deque *envs);
void	free_envs_pointer(char **envs);
void	free_data(t_data *data);
int		get_pipe_size(t_pipe *pipe);
void	init_data(t_data *data);
void	default_signal(void);
void	set_herdoc_signal(pid_t pid);
void	set_signal(pid_t pid);
char	*get_env_name(char *raw);
char	*get_env_content(char *raw);
void	ft_unset(t_simple_cmd *simple_cmd, t_deque *envs);
void	ft_export(t_simple_cmd *simple_cmd, t_deque *d_envs);
void	child_signal_handler(int signo);
void	new_prompt_handler(int signo);
int		env_name_check(char *name);
void	print_parse_error(char *msg);
void	print_syntax_error(char *msg);
int		quote_check(char *line);
int		parser(t_data *data);
t_pipe	*init_pipe();
t_cmd	*init_cmd();
t_simple_cmd	*init_simple_cmd();
t_redirects		*init_redirects();
t_redirect		*init_redirect();
int		get_pipe_size(t_pipe *pipe);
void	set_built_in_flag(t_cmd *cmd, t_token *token);
int		pipe_parser(t_pipe *pipe, t_deque *tokens);
void 	open_token(t_lexer *lexer, t_data *data);
void	append_token_content(t_lexer *lexer, t_data *data);
void	close_token(t_lexer *lexer, t_data *data);
void 	init_lexer(t_lexer *lexer);
void 	append_element(t_lexer *lexer, t_data *data);
void	init_tflag(struct termios *t);
void	init_cc(struct termios *t);
void	ft_exit(t_simple_cmd *simple_cmd);
#endif
