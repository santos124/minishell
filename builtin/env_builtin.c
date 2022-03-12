/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:20:42 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:21:45 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_path(t_all *all, char *cmd)
{
	t_env	*tmp;

	tmp = all->envp;
	while (tmp != NULL)
	{
		if (!ft_strcmp("PATH", tmp->key))
			return (0);
		tmp = tmp->next;
	}
	all->errnum = 127;
	print_error(2, NULL, cmd);
	err_exit(all->errnum, NULL);
	return (1);
}

int	check_env(char *str, t_all *all)
{
	int	i;

	i = 0;
	if (!ft_isalpha(*str))
	{
		env_print_err(all, str, "export");
		return (1);
	}
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
	{
		i++;
	}
	if (str[i] == '+' && str[i + 1] != '=')
	{
		env_print_err(all, str, "export");
		return (1);
	}
	return (0);
}

void	ft_env_error(t_all *all, char *str)
{
	all->errnum = 127;
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
}

int	ft_env(t_all *all, t_cmd *cmd)
{
	t_env	*tmp;

	if (!(all->envp))
		return (1);
	if (cmd->cmd[1])
	{
		ft_env_error(all, cmd->cmd[1]);
		return (all->errnum);
	}
	tmp = all->envp;
	while (tmp)
	{
		if (tmp->sep && !ft_strcmp(tmp->sep, "="))
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd(tmp->sep, 1);
			ft_putstr_fd(tmp->val, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
