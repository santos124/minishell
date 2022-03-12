/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:39:10 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:39:12 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*create_env(char *key, char *sep, char *val)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->key = key;
	new->sep = sep;
	new->val = val;
	new->next = 0;
	return (new);
}

void	add_env(char *env_str, t_env **start)
{
	t_env	*tmp;
	char	*key;
	char	*sep;
	char	*val;
	int		i;

	i = 0;
	sep = NULL;
	val = NULL;
	while (env_str[i] && (env_str[i] == '_' || ft_isalnum(env_str[i])))
		i++;
	key = ft_substr(env_str, 0, i);
	if (ft_strchr(env_str, '='))
		sep = ft_substr(env_str, i, 1);
	if (env_str[i + 1])
		val = ft_strdup(&env_str[i + 1]);
	if (*start == NULL)
		*start = create_env(key, sep, val);
	else
	{
		tmp = *start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_env(key, sep, val);
	}
}

static void	add_current_path(t_all *all)
{
	t_env	*tmp;
	char	*pwd;
	char	*tmp_path;
	char	*new_path;

	tmp = all->envp;
	while (ft_strcmp("PWD", tmp->key))
		tmp = tmp->next;
	pwd = tmp->val;
	tmp = all->envp;
	while (ft_strcmp("PATH", tmp->key))
		tmp = tmp->next;
	tmp_path = ft_strjoin(tmp->val, ":");
	new_path = ft_strjoin(tmp_path, pwd);
	free_null((void **)&tmp_path);
	free_null((void **)&tmp->val);
	tmp->val = ft_strdup(new_path);
	free_null((void **)&new_path);
}

void	parse_env(char **env, t_all *all)
{
	int	i;

	i = -1;
	while (env[++i])
		add_env(env[i], &all->envp);
	add_current_path(all);
}
