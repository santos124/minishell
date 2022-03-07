#include "minishell.h"

void	ft_close(t_all *all, int *file, int num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		if (!all->fd || !all->fd[i])
			continue ;
		close(all->fd[i][0]);
		close(all->fd[i][1]);
		free(all->fd[i]);
	}
	if (!file)
		return ;
	if (file[0])
		close(file[0]);
	if (file[1])
		close(file[1]);
}

void	ft_dup2(int i, int *file, t_cmd *cmd, t_all *all)
{
	int	dup2res;

	dup2res = 0;
	if (cmd->in)
		dup2res = dup2(file[0], STDIN_FILENO);
	else if (i && all->fd)
		dup2res = dup2(all->fd[i - 1][0], STDIN_FILENO);
	if (dup2res == -1)
		ft_exit(errno, "dup2"); //, all);
	if (cmd->out)
		dup2res = dup2(file[1], STDOUT_FILENO);
	else if (i < all->num - 1 && all->fd)
		dup2res = dup2(all->fd[i][1], STDOUT_FILENO);
	if (dup2res == -1)
		ft_exit(errno, "dup2"); //, all);
	ft_close(all, file, all->num - 1);
}

static void	ft_waitpid(pid_t *pid, int num, t_all *all)
{
	int	i;
	int	status;

	i = -1;
	while (++i < num)
		waitpid(-1, &status, 0);
	if (all)
	{
		if (WIFEXITED(status))
			all->errnum = WEXITSTATUS(status);
		else
			all->errnum = status + 128;
	}
	free(pid);
}

void	sig_pipex(void)
{
	signal(SIGINT, &sig_handler_child);
	signal(SIGQUIT, &sig_handler_child);
}

void	pipex(t_all *all)
{
	pid_t	*pid;
	int		i;

	pid = malloc(all->num * sizeof(pid_t));
	if (!pid)
		ft_exit(errno, "malloc"); //, all);
	i = -1;
	while (++i < all->num)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child_process(i, all);
		if (pid[i] == -1)
		{
			all->errnum = errno;
			ft_close(all, NULL, all->num - 1);
			ft_waitpid(pid, i, NULL);
			ft_exit(all->errnum, "fork"); //, all);
		}
		if (pid[i] != 0)
			sig_pipex();
	}
	ft_close(all, NULL, all->num - 1);
	ft_waitpid(pid, all->num, all);
}
