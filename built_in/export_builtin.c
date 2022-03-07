#include "../minishell.h"

int	ft_search_dups(t_env *envp, char *new)
{
	char	*newkey;
	int		i;

	i = 0;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	newkey = ft_substr(new, 0, i);
	while (envp)
	{
		if (!(ft_strcmp(envp->key, newkey)))
		{
			if (envp->val)
				envp->val = NULL;
			envp->val = ft_strdup(&new[i + 1]); //, all);
			free(newkey);
			return (1);
		}
		else
			envp = envp->next;
	}
	free(newkey);
	return (0);
}

int	if_without_all(t_env *env, t_all *all)
{
	t_env	*tmp;

	(void) env;
	sort_env(all);
	tmp = all->a_envp;
	while (tmp)
	{
		if (tmp->sep && tmp->val)
			printf("declare -x %s%s\"%s\"\n", tmp->key, \
					tmp->sep, tmp->val);
		else if (tmp->sep)
			printf("declare -x %s%s\"\"\n", tmp->key, \
					tmp->sep);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->a_z_next;
	}
	return (0);
}

static int	ft_export_join(char *new, t_env *envp)
{
	int		i;

	i = 0;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	if (new[i] == '=')
		return (0);
	while (envp)
	{
		if (!(ft_strcmp(envp->key, ft_substr(new, 0, i))))
		{
			if (envp->sep)
				free(envp->sep);
			envp->sep = ft_strdup("="); //, all);
			if (envp->val)
				envp->val = ft_strjoin(envp->val, ft_strdup(&new[i + 2]));
			else
				envp->val = ft_strdup(ft_strdup(&new[i + 2])); //, all), all);
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}

int	ft_add_new(char	*new, t_all *all)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	if (new[i] != '+')
		return (0);
	line = ft_substr(new, 0, i);
	line = ft_strjoin(line, "=");
	line = ft_strjoin(line, &new[i + 2]);
	env_add_new(line, &all->envp);
	free(line);
	return (1);
}

int	ft_export(t_all *all, t_cmd *cmd)
{
	int	i;

	i = 0;
	all->errnum = 0;
	if (!cmd->cmd[1])
		return (if_without_all(all->envp, all));
	while (cmd->cmd[++i])
	{
		if (check_arg_export(cmd->cmd[i], all))
			continue ;
		if (all->num != 1)
			break ;
		if (ft_strchr(cmd->cmd[i], '+') && \
			ft_strchr(cmd->cmd[i], '=') && \
			(ft_export_join(cmd->cmd[i], all->envp)))
			continue ;
		if (ft_search_dups(all->envp, cmd->cmd[i]))
			continue ;
		if (!ft_add_new(cmd->cmd[i], all))
			env_add_new(cmd->cmd[i], &all->envp);
	}
	return (all->errnum);
}
