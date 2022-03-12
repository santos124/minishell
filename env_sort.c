/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:31:58 by eaurelio          #+#    #+#             */
/*   Updated: 2022/03/12 19:32:01 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ch_compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}

static t_env	*sub_sort_env(t_all *all, char operation)
{
	t_env	*first;
	t_env	*tmp;

	first = all->envp;
	tmp = all->envp;
	while (tmp)
	{
		if (operation == 'f')
		{
			if (ch_compare(tmp->key, first->key) <= 0)
				first = tmp;
		}
		if (operation == 'l')
		{
			if (ch_compare(tmp->key, first->key) > 0)
				first = tmp;
		}
		tmp = tmp->next;
	}
	return (first);
}

static t_env	*sort_env_next(t_all *all, t_env *cur)
{
	t_env	*tmp;
	t_env	*new;

	tmp = all->envp;
	new = sub_sort_env(all, 'l');
	while (tmp)
	{
		if (ch_compare(tmp->key, new->key) <= 0
			&& ch_compare(tmp->key, cur->key) > 0
			&& ft_strcmp(tmp->key, "_"))
			new = tmp;
		tmp = tmp->next;
	}
	return (new);
}

void	sort_env(t_all *all)
{
	int		i;
	t_env	*cur;
	t_env	*tmp;
	t_env	*new;

	i = 0;
	tmp = all->envp;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	cur = sub_sort_env(all, 'f');
	all->a_envp = cur;
	while (i > 0)
	{
		new = sort_env_next(all, cur);
		cur->a_z_next = new;
		cur = new;
		i--;
	}
	cur->a_z_next = NULL;
}
