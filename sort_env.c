#include "minishell.h"

int ch_compare(char *s1, char *s2)
{
	int i;

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

t_env	*sub_sort_env(t_all *all, char operation)
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

t_env	*sort_env_next(t_all *all, t_env *cur)
{
	t_env	*tmp;
	t_env	*new;

	tmp = all->envp;
	new = sub_sort_env(all, 'l');
	while (tmp)
	{
		if (ch_compare(tmp->key, new->key) <= 0 &&
			ch_compare(tmp->key, cur->key) > 0 &&
			ft_strcmp(tmp->key, "_")) // убирает одну строчку
			new = tmp;
		tmp = tmp->next;
	}
	return (new);
}

void	sort_env(t_all *all) // сортировка переменной окрружения
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
	all->envp_alpha = cur; // первая строчка по алфавиту в списке env
	while (i > 0)
	{
		new = sort_env_next(all, cur);
		cur->alpha_next = new; // следующий по алфавиту в списке env
		cur = new;
		i--;
	}
	cur->alpha_next = NULL;
}
