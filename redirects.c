#include "minishell.h"

int	dup_fd(int fd) //, t_all *all) //+
{
	int	fd2;

	fd2 = dup(1);
	if (fd2 == -1)
	{
		close(fd);
		ft_exit(errno, "dup2"); //"dup"); //, all);
	}
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		close(fd2);
		ft_exit(errno, "dup2"); //, all);
	}
	return (fd2);
}

int	dup_cmd(t_command *cmd) //, t_all *all)
{
	int		fd;
	int		fd2;
	t_redir	*tmp;

	tmp = cmd->out;
	if (!cmd->out)
		return (-1);
	while (cmd->out)
	{
		if (cmd->out->two == 1)
			fd2 = open(cmd->out->name, O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			fd2 = open(cmd->out->name, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd2 == -1)
			ft_exit(errno, cmd->out->name); //, all);
		if (cmd->out->target == 1)
			fd = dup_fd(fd2); //, all);
		close(fd2);
		cmd->out = cmd->out->next;
	}
	cmd->out = tmp;
	return (fd);
}

void	redup_cmd(int fd) //, t_all *all)  //+
{
	//int	i;

	//(void)all;
	if (fd == -1)
		return ;
	//i = dup2(fd, 1);
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		ft_exit(errno, "dup2");//, all);
	}
	close(fd);
	return ;
}
