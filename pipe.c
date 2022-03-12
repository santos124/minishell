#include "minishell.h"

void	ft_dup2(int *fd, t_all *all, t_cmd *cmd, int i)
{
	int	d2;

	d2 = 0;
	if (cmd->in)
		d2 = dup2(fd[0], 0);
	else if (i && all->fd)
		d2 = dup2(all->fd[i - 1][0], 0);
	if (d2 == -1)
		err_exit(errno, "dup2");
	if (cmd->out)
		d2 = dup2(fd[1], 1);
	else if (i < all->num - 1 && all->fd)
		d2 = dup2(all->fd[i][1], 1);
	if (d2 == -1)
		err_exit(errno, "d2");
	ft_close(all, fd, all->num - 1);
}

void	ft_pipe(t_all *all)
{
	int	i;

	all->fd = (int **) malloc((all->num - 1) * sizeof(int *));
	if (!all->fd)
		err_exit(errno, "malloc");
	i = 0;
	while (i < all->num - 1)
	{
		all->fd[i] = (int *)malloc(2 * sizeof(int));
		if (!all->fd[i])
			err_exit(errno, "malloc");
		if (pipe(all->fd[i]) == -1)
		{
			while (i--)
			{
				close(all->fd[i][0]);
				close(all->fd[i][1]);
			}
			all->errnum = errno;
			err_exit(all->errnum, "pipe");
		}
		i++;
	}
}
