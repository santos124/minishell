#include "minishell.h"

int	sort_env_compare(t_env *temp, t_env *second)
{
	int	i;

	i = 0;
	while (temp->key[i])
	{
		if (temp->key[i] > second->key[i])
			return (1);
		else if (temp->key[i] < second->key[i])
			return (-1);
		else
			i++;
	}
	return (0);
}

t_env	*sort_env_find_first(t_all *all)
{
	t_env	*first;
	t_env	*temp;

	first = all->envp;
	temp = all->envp;
	while (temp)
	{
		if (sort_env_compare(temp, first) <= 0)
			first = temp;
		temp = temp->next;
	}
	return (first);
}

t_env	*sort_env_find_last(t_all *all)
{
	t_env	*first;
	t_env	*temp;

	first = all->envp;
	temp = all->envp;
	while (temp)
	{
		if (sort_env_compare(temp, first) > 0)
			first = temp;
		temp = temp->next;
	}
	return (first);
}

t_env	*sort_env_find_next(t_all *all, t_env *current)
{
	t_env	*temp;
	t_env	*new;

	temp = all->envp;
	new = sort_env_find_last(all);
	while (temp)
	{
		if (sort_env_compare(temp, new) <= 0 && \
			sort_env_compare(temp, current) > 0 && \
			ft_strcmp(temp->key, "_"))
			new = temp;
		temp = temp->next;
	}
	return (new);
}

void	sort_env(t_all *all)
{
	t_env	*current;
	t_env	*new;
	t_env	*temp;
	int		i;

	i = 0;
	temp = all->envp;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	current = sort_env_find_first(all);
	all->envp_alpha = current;
	while (i > 0)
	{
		new = sort_env_find_next(all, current);
		current->alpha_next = new;
		current = new;
		i--;
	}
	current->alpha_next = NULL;
}
