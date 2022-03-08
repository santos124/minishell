#include "../minishell.h"

static char	*replace_str(char *line, char *old, char *new, int start)
{
	int		i;
	int		j;
	int		k;
	char	*result;
	int		res_len;

	i = 0;
	j = 0;
	k = 0;
	res_len = ft_strlen(line) - ft_strlen(old) + ft_strlen(new);
	result = malloc(sizeof(*line) * res_len);
	while (i < res_len && i < start)
	{
		result[i] = line[i];
		i++;
	}
	k = i + ft_strlen(old) + 1;
	while (new[j])
		result[i++] = new[j++];
	while (line[k])
		result[i++] = line[k++];
	result[i] = '\0';
	return (result);
}

char	*replace_env(char *line, int *i, t_env *envp)
{
	int		begin;
	char	*env_key;
	char	*env_val;
	t_env	*temp;

	begin = *i;
	env_val = ft_strdup(""); //, all);
	(*i)++;
	while (line[*i] && (line[*i] == '_' || ft_isalnum(line[*i])))
		(*i)++;
	env_key = ft_substr(line, begin + 1, *i - begin - 1);
	temp = envp;
	while (temp)
	{
		if (ft_strcmp(temp->key, env_key) == 0)
		{
			free(env_val);
			env_val = temp->val;
		}
		temp = temp->next;
	}
	line = replace_str(line, env_key, env_val, begin);
	*i = begin + ft_strlen(env_val) - 1;
	free(env_key);
	return (line);
}

char	*get_last_exit_code(char *line, t_all *all, int *i)
{
	char	*exit_code;

	exit_code = ft_itoa(all->errnum);
	line = replace_str(line, "?", exit_code, *i);
	return (line);
}
