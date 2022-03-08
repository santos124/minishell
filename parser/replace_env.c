#include "../minishell.h"

static char	*replace_str(char *str, char *old, char *new, int start)
{
	char	*ret;
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(str) - ft_strlen(old) + ft_strlen(new);
	ret = (char *)malloc(sizeof(*str) * len);
	while (i < start && i < len)
	{
		ret[i] = str[i];
		i++;
	}
	k = i + ft_strlen(old) + 1;
	while (new[j])
		ret[i++] = new[j++];
	while (str[k])
		ret[i++] = str[k++];
	ret[i] = '\0';
	return (ret);
}

char	*replace_env(char *str, int *i, t_env *envp)
{
	int		begin;
	char	*env_key;
	char	*env_val;
	t_env	*temp;

	begin = *i;
	env_val = ft_strdup(""); //, all);
	(*i)++;
	while (str[*i] && (str[*i] == '_' || ft_isalnum(str[*i])))
		(*i)++;
	env_key = ft_substr(str, begin + 1, *i - begin - 1);
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
	str = replace_str(str, env_key, env_val, begin);
	*i = begin + ft_strlen(env_val) - 1;
	free(env_key);
	return (str);
}

char	*get_last_exit_code(char *str, t_all *all, int *i)
{
	char	*exit_code;

	exit_code = ft_itoa(all->errnum);
	str = replace_str(str, "?", exit_code, *i);
	return (str);
}
