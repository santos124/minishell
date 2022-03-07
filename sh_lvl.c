#include "minishell.h"

static void	ft_sub_shlvl(t_env *tmp, int level) //+
{
	if (!tmp->val[0])
	{
		free(tmp->sep);
		tmp->sep = ft_strdup("="); //, all);
		free(tmp->val);
		tmp->val = ft_strdup("1"); //, all);
	}
	else
	{
		level = ft_atoi(tmp->val) + 1;
		free(tmp->val);
		tmp->val = ft_itoa(level);
	}
}


void	ft_shlvl_check(t_all *all) //+
{
	t_env	*tmp;
	int		level;

	tmp = all->envp;
	level = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL"))
		{
			ft_sub_shlvl( tmp, level);
			return ;
		}
		tmp = tmp->next;
	}
	env_add_new("SHLVL=1", &all->envp);
}
