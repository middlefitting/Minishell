#include "parser.h"

t_pipe *init_pipe()
{
	t_pipe	*pipe;

	pipe = 0;
	while (!pipe)
		pipe = ft_calloc(1, sizeof(t_pipe));
	return (pipe);
}

t_cmd *init_cmd()
{
	t_cmd	*cmd;

	cmd = 0;
	while (!cmd)
		cmd = ft_calloc(1, sizeof(t_cmd));
	return (cmd);
}

t_simple_cmd *init_simple_cmd()
{
	t_simple_cmd	*simple_cmd;

	simple_cmd = 0;
	while (!simple_cmd)
		simple_cmd = ft_calloc(1, sizeof(t_simple_cmd));
	return (simple_cmd);
}

t_redirects	*init_redirects()
{
	t_redirects	*redirects;

	redirects = 0;
	while(!redirects)
		redirects = ft_calloc(1, sizeof(t_redirects));
	return (redirects);
}

t_redirect	*init_redirect()
{
	t_redirect	*redirect;

	redirect = 0;
	while(!redirect)
		redirect = ft_calloc(1, sizeof(t_redirect));
	return (redirect);
}
