#include "minishell.h"

//static void	ft_close(t_all *all, int *fd, int num)
//{
//	int	i;
//
//	i = 0;
//	while (i < num)
//	{
//		if (!all->fd || !all->fd[i])
//			continue ;
//		close(all->fd[i][0]);
//		close(all->fd[i][1]);
//		free_null((void**)&all->fd[i]);
//		i++;
//	}
//	if (!fd)
//		return ;
//	if (fd[0])
//		close(fd[0]);
//	if (fd[1])
//		close(fd[1]);
//}

static void	ft_close_fd(int *fd) // +
{
	if (!fd)
		return ;
	if (fd[0])
		close(fd[0]);
	if (fd[1])
		close(fd[1]);
};

static void ft_close(t_all *all, int *fd, int num) // +
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (!all->fd || !all->fd[i])
			continue ;
		close(all->fd[i][0]);
		close(all->fd[i][1]);
		free_null((void**)&all->fd[i]);
		i++;
		ft_close_fd(fd);
	}
}

void	ft_dup2(int *fd, t_all *all, t_cmd *cmd, int i) // + создает копию
// файлового дескриптора для каждого процесса
{
	int	d2;

	d2 = 0;
	if (cmd->in) //входящая команда
		d2 = dup2(fd[0], 0); // из в
	else if (i && all->fd)
		d2 = dup2(all->fd[i - 1][0], 0); // если не первый
	if (d2 == -1)
		err_exit(errno, "dup2");
	if (cmd->out) // выходящий
		d2 = dup2(fd[1], 1);
	else if (i < all->num - 1 && all->fd) // если не последний
		d2 = dup2(all->fd[i][1], 1);
	if (d2 == -1)
		err_exit(errno, "d2");
	ft_close(all, fd, all->num - 1);
}

static void	ft_waitpid(pid_t *pid, int num, t_all *all) // ???
{
	int	i;
	int	status;

	i = 0;
	while (i < num)
	{
		waitpid(-1, &status, 0); //optinons 0, так как не учитываем;
		// пид:
		// < -1 - означает, что нужно ждать любого дочернего процесса,
		// идентификатор группы процессов которого равен абсолютному значению pid.
		//-1 - означает ожидание любого дочернего процесса;
		//0 -означает ожидание любого дочернего процесса, идентификатор группы
		// процессов которого равен идентификатору текущего процесса.
		//> 0 - означает ожидание дочернего процесса, чей идентификатор равен
		// pid.
		i++;
	}
	if (all)
	{
		if (WIFEXITED(status)) // != 0, если дочерний процесс успешно завершился
			all->errnum = WEXITSTATUS(status); // возвращает восемь младших
			// битов значения, которое вернул завершившийся дочерний процесс
			// (то есть 0)
		else
			all->errnum = status + 128; // errnum = 128 ?????
	}
	free_null((void**)&pid);
}

void	pipex(t_all *all) // +
{
	int		i;
	pid_t	*pid;

	i = 0;
	pid = (pid_t *)malloc(all->num * sizeof(pid_t));
	if (!pid)
		err_exit(errno, "malloc");
	while (i < all->num)
	{
		pid[i] = fork(); // возвращает пид 0 ребенку и пид ребенка родителю
		if (pid[i] == 0) // для ребенка
			run_child(i, all);
		if (pid[i] == -1)  // для родителя
		{
			all->errnum = errno;
			ft_close(all, NULL, all->num - 1);
			ft_waitpid(pid, i, NULL);
			err_exit(all->errnum, "fork");
		}
		if (pid[i] != 0) // для родителя, если все ок
		{
			signal(SIGINT, &handler_child);
			signal(SIGQUIT, &handler_child);
		}
		i++;
	}
	ft_close(all, NULL, all->num - 1);
	ft_waitpid(pid, all->num, all);
}



//i = -1;
//while (++i < all->num)
//{
//	pid[i] = fork();
//	if (pid[i] == 0)
//		run_child(i, all);
//	if (pid[i] == -1)
//	{
//		all->errnum = errno;
//		ft_close(all, NULL, all->num - 1);
//		ft_waitpid(pid, i, NULL);
//		err_exit(all->errnum, "fork"); //, all);
//	}
//	if (pid[i] != 0)
//	sig_pipex();
//}
//ft_close(all, NULL, all->num - 1);
//ft_waitpid(pid, all->num, all);
