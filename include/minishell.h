/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: middlefitting <middlefitting@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:39:58 by sechung           #+#    #+#             */
/*   Updated: 2023/03/27 12:49:11 by middlefitti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <sys/stat.h>
# include <stdio.h>
# include <term.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define BUFFER_SIZE	1024
# define READ			0
# define WRITE			1
# define ERROR			-1

int	g_exit_status;

enum	e_token_type {
	DEFAULT,
	WORD,
	PIPE,
	REDIRECTION,
	HEREDOC,
	PATH,
};

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
	int		token_flag;
	t_deque	*tokens;
	t_token	*token;
}	t_lexer;

typedef struct s_redirect
{
	t_token	*type;
	t_token	*file_name;
}	t_redirect;

typedef struct s_redirects
{
	t_redirect			*redirect;
	struct s_redirects	*redirects;
}	t_redirects;

typedef struct s_simple_cmd
{
	t_token	*file_path;
	t_deque	*argv;
	int		built_in_flag;
}	t_simple_cmd;

typedef struct s_cmd
{
	t_redirects		*redirects;
	t_simple_cmd	*simple_cmd;
}	t_cmd;

typedef struct s_pipe
{
	t_cmd			*cmd;
	struct s_pipe	*pipe;
}	t_pipe;

typedef struct s_data
{
	char	*line;
	t_deque	*tokens;
	t_deque	*envs;
	t_pipe	*tree;
}	t_data;

typedef struct s_process
{
	t_deque	*envp;
	t_pipe	*pipe;
	pid_t	pid;
	char	**heredoc_file;
	int		heredoc_flag;
	int		num_of_pipe;
	int		fd_idx;
	int		**fds;
	int		cmd;
	int		std_in;
	int		std_out;
}	t_process;

void			exec(t_pipe *tree, t_deque *envp);
t_process		*init_proc(t_pipe *tree, t_deque *envp);
void			do_pipe(t_process *proc);
int				do_fork(t_process *proc, t_pipe *tmp);
void			do_cmds(t_process *proc);
void			do_cmd(t_process *proc);
void			exit_proc(t_process *proc);
void			do_builtins(t_process *proc, int flag);
void			fork_and_pipe(t_process *proc, int flag);

void			check_redir(t_process *proc);
void			check_outfile(t_process *proc, t_token *file, char *content);
void			check_file(t_process *proc, t_redirects *redirects, int fd);

void			mk_heredoc(t_process *proc);
void			check_heredoc(t_process *proc, t_redirects *redirects);
int				write_str(char *content, int fd, t_deque *envs);
void			mk_num(char *str, int num);
char			*mk_filename(void);
void			rm_heredoc(void);
void			is_heredoc(t_process *proc);

void			close_and_dup(t_process *proc);
void			close_fds(t_process *proc, int check_parent);
void			close_fd(t_process *proc);

void			make_path(t_process *proc);
char			**get_option(t_process *proc);
void			check_infile(t_process *proc,
					t_redirects *redirects, t_token *file, char *content);
void			do_execve(t_process *proc, char **tmp,
					char **option, char *cmd);

char			**m_split(char const *s, char c);
int				m_str_count(char *str, char c);
char			*m_indiv_str(int str_len, char *str);
int				m_str_len(char **str, char c);

int				m_strncmp(const char *s1, const char *s2, size_t n);
void			*m_calloc(size_t count, size_t size);
void			m_bzero(void *s, size_t n);
void			*m_memset(void *b, int c, size_t len);
char			*m_strjoin(char const *s1, char const *s2);
size_t			m_strlen(const char *str);
size_t			m_strlcat(char *dst, const char *src, size_t dstsize);
t_token			*check_echo_option(t_deque *argv, int *option);
void			print_error(const char *cmd, char *option, int flags);
void			print_errortype(char *str, int flags);
int				heredoc_fork(t_process *proc);
void			fork_error(void);

int				check_isbuiltins(t_process *proc);
void			m_echo(t_process *proc, t_deque *argv, int flag);
int				is_option(char *content);
void			m_cd(t_process *proc, int flag);
void			m_pwd(t_process *proc, int flag);
void			m_export(t_process *proc, int flag);
void			m_unset(t_process *proc, int flag);
void			m_env(t_process *proc, int flag);
void			write_env(t_token *env, int env_flag);
void			path_error(char *path, char *home, int opt_flag);
void			mexit(int flag, int mexit_status);
void			recover_std(t_process *proc);
void			save_std(t_process *proc);
void			update_pwd(t_process *proc, char *tmp);
void			check_patherror(char *path, char *home, int opt_flag);
char			*check_cdopt(t_process *proc, char *path, int *opt_flag);

void			free_proc(t_process *proc);
void			free_all(char **str);
void			free_heredoc(t_process *proc);

t_deque			*get_deque(void);
void			append(t_deque *deque, t_token *token);
void			appendleft(t_deque *deque, t_token *token);
t_token			*pop(t_deque *deque);
t_token			*popleft(t_deque *deque);
t_token			*get_token(void);
void			free_deque_with_token(t_deque *deque);
void			free_deque(t_deque *deque);
void			free_token(t_token *token);
int				parse(t_data *data);
void			free_pipe(t_pipe *pipe);
void			env_init(t_data *data, char **envp);
t_token			*get_env_token(void);
char			*get_env(t_deque *envs, char *name);
void			env_append(t_deque *envs, char *raw);
int				white_space(char c);
int				env_parser(t_data *data);
int				renew_quote_flag(int flag, char c);
char			*join_line(char *dest, char *s);
void			remove_env(t_deque *envs, char *name);
char			**get_envs_pointer(t_deque *envs);
void			free_envs_pointer(char **envs);
void			free_data(t_data *data);
int				get_pipe_size(t_pipe *pipe);
void			init_data(t_data *data);
void			default_signal(void);
void			set_herdoc_signal(void);
void			set_signal(pid_t pid);
char			*get_env_name(char *raw);
char			*get_env_content(char *raw);
void			ft_unset(t_simple_cmd *simple_cmd, t_deque *envs);
void			ft_export(t_simple_cmd *simple_cmd, t_deque *d_envs);
void			child_signal_handler(int signo);
void			new_prompt_handler(int signo);
int				env_name_check(char *name);
void			print_parse_error(char *msg);
void			print_syntax_error(char *msg);
int				quote_check(char *line);
int				parser(t_data *data);
t_pipe			*init_pipe(void);
t_cmd			*init_cmd(void);
t_simple_cmd	*init_simple_cmd(void);
t_redirects		*init_redirects(void);
t_redirect		*init_redirect(void);
int				get_pipe_size(t_pipe *pipe);
void			set_built_in_flag(t_cmd *cmd, t_token *token);
int				pipe_parser(t_pipe *pipe, t_deque *tokens);
void			open_token(t_lexer *lexer, t_data *data);
void			append_token_content(t_lexer *lexer, t_data *data);
void			close_token(t_lexer *lexer, t_data *data);
void			init_lexer(t_lexer *lexer);
void			append_element(t_lexer *lexer, t_data *data);
void			init_tflag(struct termios *t);
void			init_cc(struct termios *t);
void			ft_exit(t_simple_cmd *simple_cmd, int num_of_pipe);
void			renew_line(t_data *data, int *s_e, int *index, int quote_flag);
char			*heredoc_parser(char *line, t_deque *envs);
int				ft_longtoi(const char *str, int *flag);
#endif
