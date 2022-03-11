#include "../minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (!ft_strcmp(str, "-n"))
		return (1);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n = 0;

	i = 0;
	if (!cmd->cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (cmd->cmd[1][0] == '-' && check_n(cmd->cmd[1]))
	{
		i = 1;
		n = 1;
	}
	while (cmd->cmd[++i])
	{
		if (ft_strcmp(cmd->cmd[i], "-n") || !n)
		{
			ft_putstr_fd(cmd->cmd[i], 1);
			if (cmd->cmd[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
	}
	if (!check_n(cmd->cmd[1]))
		ft_putstr_fd("\n", 1);
	return (0);
}
