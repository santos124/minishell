#include "minishell.h"

static void	dup2_fd(int fd, int fd2) //+
{
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		close(fd2);
		err_exit(errno, "dup2");
	}
}

static int	dup_fd(int fd) //+
{
	int	fd2;

	fd2 = dup(1);
	if (fd2 == -1)
	{
		close(fd);
		err_exit(errno, "dup");
	}
	dup2_fd(fd, fd2);
	return (fd2);
}

int	dup_cmd(t_cmd *cmd) // +
{
	int		fd;
	int		fd2;
	t_red	*tmp;

	tmp = cmd->out;
	if (!cmd->out)
		return (-1);
	while (cmd->out)
	{
		if (cmd->out->doub == 1)
			fd = open(cmd->out->name, O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			fd = open(cmd->out->name, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			err_exit(errno, cmd->out->name); //, all);
		if (cmd->out->last == 1)
			fd2 = dup_fd(fd);
		close(fd);
		cmd->out = cmd->out->next;
	}
	cmd->out = tmp;
	return (fd2);
}

void	redup_cmd(int fd)  //+
{
	//int	i;

	//(void)all;
	if (fd == -1)
		return ;
	//i = dup2(fd, 1);
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		err_exit(errno, "dup2");//, all);
	}
	close(fd);
	return ;
}