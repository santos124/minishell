#include "../minishell.h"

int	ft_search_dups(t_env *env, char *new)
{
	int		i;
	char	*newkey;

	i = 0;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	newkey = ft_substr(new, 0, i);
	while (env)
	{
		if (!(ft_strcmp(env->key, newkey)))
		{
			if (env->val)
				env->val = NULL;
			env->val = ft_strdup(&new[i + 1]); //, all);
			free_null((void**)&newkey);
			return (1);
		}
		else
			env = env->next;
	}
	free_null((void**)&newkey);
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
			printf("declare -x %s%s\"%s\"\n", tmp->key,tmp->sep, tmp->val);
		else if (tmp->sep)
			printf("declare -x %s%s\"\"\n", tmp->key, tmp->sep);
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
				free_null((void**)&envp->sep);
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

static int	env_add(char	*new, t_all *all)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (new[i] && (new[i] == '_' || ft_isalnum(new[i])))
		i++;
	if (new[i] != '+')
		return (0);
	str = ft_substr(new, 0, i);
	str = ft_strjoin(str, "=");
	str = ft_strjoin(str, &new[i + 2]);
	add_env(str, &all->envp);
	free_null((void**)&str);
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
		if (check_env(cmd->cmd[i], all))
			continue ;
		if (all->num != 1)
			break ;
		if (ft_strchr(cmd->cmd[i], '+') && \
			ft_strchr(cmd->cmd[i], '=') && \
			(ft_export_join(cmd->cmd[i], all->envp)))
			continue ;
		if (ft_search_dups(all->envp, cmd->cmd[i]))
			continue ;
		if (!env_add(cmd->cmd[i], all))
			add_env(cmd->cmd[i], &all->envp);
	}
	return (all->errnum);
}
