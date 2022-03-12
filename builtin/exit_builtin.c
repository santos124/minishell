/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:20:27 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:20:28 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isalldigit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
		if (!ft_isdigit((unsigned char)str[i]) || ft_strlen(str) >= 19)
			return (1);
	return (0);
}

int	err_exit(int errnum, char *msg)
{
	char	*errmsg;

	if (msg)
	{
		errmsg = strerror(errnum);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(errmsg, 2);
		ft_putstr_fd("\n", 2);
		exit(errnum);
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
	if (cmd && cmd->cmd[1] && !ft_isalldigit(cmd->cmd[1]))
		err_exit((unsigned char)ft_atoi(all->cmd->cmd[1]), NULL);
	else if (cmd->cmd[1])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		err_exit(255, NULL);
	}
	else
		err_exit(0, NULL);
	return (0);
}
