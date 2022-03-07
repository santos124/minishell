#include "minishell.h"

void	ft_sub_shlvl(t_all *all, t_env *tmp, int level)
{
	if (!tmp->value[0])
	{
		free(tmp->separator);
		tmp->separator = ft_strdup("=", all);
		free(tmp->value);
		tmp->value = ft_strdup("1", all);
	}
	else
	{
		level = ft_atoi(tmp->value) + 1;
		free(tmp->value);
		tmp->value = ft_itoa(level, all);
	}
}


void	ft_shlvl_check(t_all *all)
{
	t_env	*tmp;
	int		level;

	tmp = all->envp;
	level = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL"))
		{
			ft_sub_shlvl(all, tmp, level);
			return ;
		}
		tmp = tmp->next;
	}
	env_add_new("SHLVL=1", &all->envp, all);
}
