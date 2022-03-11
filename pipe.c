#include "minishell.h"

void	ft_pipe(t_all *all) // +
{
	int i;

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


//
//
//	i = -1;
//	while (++i < all->num - 1)
//	{
//		all->fd[i] = malloc(2 * sizeof(int));
//		if (!all->fd[i])
//			err_exit(errno, "malloc");
//		if (pipe(all->fd[i]) == -1)
//		{
//			all->errnum = errno;
//			while (i--)
//			{
//				close(all->fd[i][0]);
//				close(all->fd[i][1]);
//			}
//			err_exit(all->errnum, "pipe");
//		}
//	}



