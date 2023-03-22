#ifndef EXEC_H
# define EXEC_H

# include <errno.h>
# include <sys/stat.h>
# include "parser.h"

# define BUFFER_SIZE	1024
# define READ			0
# define WRITE			1
# define ERROR			-1

int	g_exit_status;
typedef struct s_process
{
	t_deque	*envp;
	t_pipe	*pipe;
	pid_t	pid;
	char	**heredoc_file;
	int		num_of_pipe;
	int		fd_idx;
	int		**fds;
	int		cmd;
	int		std_in;
	int		std_out;
}	t_process;

void		exec(t_pipe *tree, t_deque *envp);
t_process	*init_proc(t_pipe *tree, t_deque *envp);
void		do_pipe(t_process *proc, t_pipe *tree);
int			do_fork(t_process *proc, t_pipe *tree);
void		do_cmds(t_process *proc);
void		do_cmd(t_process *proc);
void		exit_proc(t_process *proc);
void		do_builtins(t_process *proc, int flag);
//--------------------------  check_redir.c
void		check_redir(t_process *proc);
void		check_infile(t_process *proc, t_redirects *redirects,
				t_token *file, char *content);
void		check_outfile(t_process *proc, t_token *file, char *content);
void		check_file(t_process *proc, t_redirects *redirects, int fd);
//--------------------------  here_doc.c
void		mk_heredoc(t_process *proc);
void		check_heredoc(t_process *proc, t_redirects *redirects);
void		mk_num(char *str, int num);
char		*mk_filename(void);
void		rm_heredoc(void);
//--------------------------  close.c
void		close_and_dup(t_process *proc);
void		close_fds(t_process *proc, int check_parent);
void		close_fd(t_process *proc);
//--------------------------  make_path.c
void		make_path(t_process *proc);
char		**get_option(t_process *proc);
void		do_execve(t_process *proc, char **tmp, char **option, char *cmd);
//--------------------------  m_split.c
char		**m_split(char const *s, char c);
int			m_str_count(char *str, char c);
char		*m_indiv_str(int str_len, char *str);
int			m_str_len(char **str, char c);
//--------------------------  m_function 1 & 2.c
int			m_strncmp(const char *s1, const char *s2, size_t n);
void		*m_calloc(size_t count, size_t size);
void		m_bzero(void *s, size_t n);
void		*m_memset(void *b, int c, size_t len);
char		*m_strjoin(char const *s1, char const *s2);
size_t		m_strlen(const char *str);
size_t		m_strlcat(char *dst, const char *src, size_t dstsize);
t_token		*check_echo_option(t_deque *argv, int *option);
void		print_error(const char *cmd, char *option, int flags);
void		print_errortype(char *str, int flags);
//--------------------------  m_builtins 1 & 2.c
int			check_isbuiltins(t_process *proc);
void		m_echo(t_process *proc, t_deque *argv, int flag);
void		m_cd(t_process *proc, int flag);
void		m_pwd(t_process *proc, int flag);
void		m_export(t_process *proc, int flag);
void		m_unset(t_process *proc, int flag);
void		m_env(t_process *proc, int flag);
void		path_error(char *path);
void		mexit(int flag, int mexit_status);
void		recover_std(t_process *proc);
void		save_std(t_process *proc);
//--------------------------  free.c
void		free_proc(t_process *proc);
void		free_all(char **str);
void		free_heredoc(t_process *proc);
#endif
