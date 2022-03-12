#include "minishell.h"

static void	ft_sub_shlvl(t_env *tmp, int level)
{
	if (!tmp->val[0])
	{
		free_null((void **)&tmp->sep);
		tmp->sep = ft_strdup("=");
		free_null((void **)&tmp->val);
		tmp->val = ft_strdup("1");
	}
	else
	{
		level = ft_atoi(tmp->val) + 1;
		free_null((void **)&tmp->val);
		tmp->val = ft_itoa(level);
	}
}

void	shlvl_check(t_all *all)
{
	t_env	*tmp;
	int		level;

	tmp = all->envp;
	level = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL"))
		{
			ft_sub_shlvl(tmp, level);
			return ;
		}
		tmp = tmp->next;
	}
	add_env("SHLVL=1", &all->envp);
}
