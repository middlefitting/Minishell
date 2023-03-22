#include "exec.h"

int	check_isbuiltins(t_process *proc)
{
	if (proc->pipe->cmd->simple_cmd == NULL)
	{
		check_redir (proc);
		recover_std (proc);
		return (1);
	}
	if (proc->pipe->cmd->simple_cmd->built_in_flag)
	{
		check_redir (proc);
		do_builtins (proc, 0);
		recover_std (proc);
		return (1);
	}
	return (0);
}

void	do_builtins(t_process *proc, int flag)
{
	char	*cmd;

	cmd = proc->pipe->cmd->simple_cmd->file_path->content;
	if (!ft_strcmp ("echo", cmd))
		m_echo(proc, proc->pipe->cmd->simple_cmd->argv, flag);
	else if (!ft_strcmp ("cd", cmd))
		m_cd(proc, flag);
	else if (!ft_strcmp ("pwd", cmd))
		m_pwd(proc, flag);
	else if (!ft_strcmp ("export", cmd))
		ft_export(proc->pipe->cmd->simple_cmd, proc->envp);
	else if (!ft_strcmp ("unset", cmd))
		ft_unset(proc->pipe->cmd->simple_cmd, proc->envp);
	else if (!ft_strcmp ("env", cmd))
		m_env(proc, flag);
	else if (!ft_strcmp ("exit", cmd))
		exit (0);
	if (flag)
		exit (g_exit_status);
	else
		return ;
}
