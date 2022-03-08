#include "../minishell.h"

static int	ft_isalldigit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit((unsigned char)str[i]) || ft_strlen(str) >= 19)
			return (1);
	}
	return (0);
}

int	err_exit(int errnum, char *msg) //, t_all *all)
{
	char	*errmsg;

	//(void)all;
	if (msg)
	{
		errmsg = strerror(errnum);
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
		write(2, errmsg, ft_strlen(errmsg));
		write(2, "\n", 1);
	}
	exit(errnum);
}

int	ft_exit(t_all *all, t_cmd *cmd)
{
	if (all->num == 1)
		ft_putstr_fd("exit\n", 1);
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (cmd->cmd[1] && !ft_isalldigit(cmd->cmd[1]))
		err_exit((unsigned char)ft_atoi(all->cmd->cmd[1]), NULL); //, all);
	else if (cmd->cmd[1])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		err_exit(255, NULL); //, all);
	}
	else
		err_exit(0, NULL); //, all);
	return (0);
}
