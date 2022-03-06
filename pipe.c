#include "minishell.h"

void	ft_pipe(t_all *all)
{
	int	i;

	all->fd = malloc((all->num - 1) * sizeof(int *));
	if (!all->fd)
		ft_exit(errno, "malloc", all);
	i = -1;
	while (++i < all->num - 1)
	{
		all->fd[i] = malloc(2 * sizeof(int));
		if (!all->fd[i])
			ft_exit(errno, "malloc", all);
		if (pipe(all->fd[i]) == -1)
		{
			all->errnum = errno;
			while (i--)
			{
				close(all->fd[i][0]);
				close(all->fd[i][1]);
			}
			ft_exit(all->errnum, "pipe", all);
		}
	}
}
