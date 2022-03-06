#include "minishell.h"

int	dup_fd(int file, t_all *all)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (fd == -1)
	{
		close(file);
		ft_exit(errno, "dup", all);
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		close(file);
		close(fd);
		ft_exit(errno, "dup2", all);
	}
	return (fd);
}

int	dup_cmd(t_command *cmd, t_all *all)
{
	int		fd;
	int		file;
	t_redir	*temp;

	temp = cmd->out;
	if (!cmd->out)
		return (-1);
	while (cmd->out)
	{
		if (cmd->out->two == 1)
			file = open(cmd->out->name, O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			file = open(cmd->out->name, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (file == -1)
			ft_exit(errno, cmd->out->name, all);
		if (cmd->out->target == 1)
			fd = dup_fd(file, all);
		close(file);
		cmd->out = cmd->out->next;
	}
	cmd->out = temp;
	return (fd);
}

void	redup_cmd(int fd, t_all *all)
{
	int	i;

	(void)all;
	if (fd == -1)
		return ;
	i = dup2(fd, STDOUT_FILENO);
	if (i == -1)
	{
		close(fd);
		ft_exit(errno, "dup2", all);
	}
	close(fd);
	return ;
}
