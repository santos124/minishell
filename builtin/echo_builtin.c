/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:21:52 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:27:57 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	i = 0;
	if (!cmd->cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (cmd->cmd[1][0] == '-' && check_n(cmd->cmd[1]))
		i = 1;
	while (cmd->cmd[++i])
	{
		if (ft_strcmp(cmd->cmd[i], "-n") || !check_n(cmd->cmd[1]))
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
