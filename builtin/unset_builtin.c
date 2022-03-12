/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:35:04 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:15:24 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_del_env(t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	env->next = tmp->next;
	free_null((void **)&tmp->key);
	free_null((void **)&tmp->sep);
	free_null((void **)&tmp->val);
	free_null((void **)&tmp);
}

int	ft_check_first(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	if (!ft_strcmp(str, tmp->key))
	{
		*env = (*env)->next;
		free_null((void **)&tmp->key);
		free_null((void **)&tmp->sep);
		free_null((void **)&tmp->val);
		free_null((void **)&tmp);
		return (1);
	}
	return (0);
}

void	env_print_err(t_all *all, char *str, char *namecmd)
{
	all->errnum = 1;
	ft_putstr_fd(namecmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_check_error(char *cmd, t_all *all)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (!(ft_isalpha(cmd[j])) && (cmd[j] != '_'))
		{
			env_print_err(all, cmd, "unset");
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_unset(t_cmd *cmd, t_all *all)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		i;

	i = 0;
	while (cmd->cmd[++i])
	{
		if (ft_check_error(cmd->cmd[i], all) || !all->envp)
			return (1);
		if (cmd->cmd[i][0] == '_')
			continue ;
		if (ft_check_first(&all->envp, cmd->cmd[i]))
			continue ;
		tmp1 = all->envp;
		tmp2 = tmp1->next;
		while (tmp2 && ft_strcmp(cmd->cmd[i], tmp2->key))
		{
			tmp1 = tmp2;
			tmp2 = tmp2->next;
		}
		if (tmp2)
			ft_del_env(tmp1);
	}
	return (0);
}
