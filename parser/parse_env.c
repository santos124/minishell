#include "../minishell.h"

t_env	*env_create_new(char *key, char *sep, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = key;
	new->separator = sep;
	new->value = value;
	new->next = NULL;
	return (new);
}

//добавить одну переменную среды
void	env_add_new(char *env_line, t_env **first, t_all *all)
{
	t_env	*tmp;
	char	*key;
	char	*sep;
	char	*value;
	int		i;

	i = 0;
	sep = NULL;
	value = NULL;
	while (env_line[i] && (env_line[i] == '_' || ft_isalnum(env_line[i])))
		i++;
	key = ft_substr(env_line, 0, i, all);
	if (ft_strchr(env_line, '='))
		sep = ft_substr(env_line, i, 1, all);
	if (env_line[i + 1])
		value = ft_strdup(&env_line[i + 1], all);
	if (*first == NULL)
		*first = env_create_new(key, sep, value);
	else
	{
		tmp = *first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = env_create_new(key, sep, value);
	}
}

//добавить текущий путь
void	add_current_path(t_all *all)
{
	t_env	*temp;
	char	*pwd;
	char	*temp_path;
	char	*new_path;

	temp = all->envp;
	while (ft_strcmp(temp->key, "PWD") != 0)
		temp = temp->next;
	pwd = temp->value;
	temp = all->envp;
	while (ft_strcmp(temp->key, "PATH") != 0)
		temp = temp->next;
	temp_path = ft_strjoin(temp->value, ":", all);
	new_path = ft_strjoin(temp_path, pwd, all);
	free(temp->value);
	temp->value = ft_strdup(new_path, all);
	free(temp_path);
	free(new_path);
}

//взятие переменных среды
void	parse_env(char **envp, t_all *all)
{
	int	i;

	i = -1;
	while (envp[++i])
		env_add_new(envp[i], &all->envp, all);
	add_current_path(all);
}
