#include "minishell.h"

void	ft_shlvl_check(t_all *all)
{
	t_env	*tmp;
	int		value;

	tmp = all->envp;
	value = 1;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL") && !tmp->value[0])
		{
			free(tmp->separator);
			tmp->separator = ft_strdup("=", all);
			free(tmp->value);
			tmp->value = ft_strdup("1", all);
			return ;
		}
		else if (!ft_strcmp(tmp->key, "SHLVL") && tmp->value[0])
		{
			value += ft_atoi(tmp->value);
			free(tmp->value);
			tmp->value = ft_itoa(value, all);
			return ;
		}
		tmp = tmp->next;
	}
	env_add_new("SHLVL=1", &all->envp, all);
}
