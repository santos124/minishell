#include "minishell.h"

static void	ft_close_fd(int *fd)
{
	if (!fd)
		return ;
	if (fd[0])
		close(fd[0]);
	if (fd[1])
		close(fd[1]);
}

void	ft_close(t_all *all, int *fd, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (!all->fd || !all->fd[i])
			continue ;
		close(all->fd[i][0]);
		close(all->fd[i][1]);
		free_null((void **)&all->fd[i]);
		i++;
		ft_close_fd(fd);
	}
}

static void	ft_waitpid(pid_t *pid, int num, t_all *all)
{
	int	i;
	int	status;

	i = 0;
	while (i < num)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	if (all)
	{
		if (WIFEXITED(status))
			all->errnum = WEXITSTATUS(status);
		else
			all->errnum = status + 128;
	}
	free_null((void **)&pid);
}

static	pid_t	*sub_pipex(t_all **all, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < (*all)->num)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			run_child(i, *all);
		if (pid[i] == -1)
		{
			(*all)->errnum = errno;
			ft_close(*all, NULL, (*all)->num - 1);
			ft_waitpid(pid, i, NULL);
			err_exit((*all)->errnum, "fork");
		}
		if (pid[i] != 0)
		{
			signal(SIGINT, &handler_child);
			signal(SIGQUIT, &handler_child);
		}
		i++;
	}
	return (pid);
}

void	pipex(t_all *all)
{
	pid_t	*pid;

	pid = (pid_t *)malloc(all->num * sizeof(pid_t));
	if (!pid)
		err_exit(errno, "malloc");
	pid = sub_pipex(&all, pid);
	ft_close(all, NULL, all->num - 1);
	ft_waitpid(pid, all->num, all);
}
