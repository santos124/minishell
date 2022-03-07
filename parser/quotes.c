#include "../minishell.h"

void	remove_quotes(char *str, int start, int *i)
{
	int	len;
	int	j;

	len = ft_strlen(str);
	j = 0;
	while (start + j < *i - 1)
	{
		str[start + j] = str[start + j + 1];
		j++;
	}
	while (start + j < len - 2)
	{
		str[start + j] = str[start + j + 2];
		j++;
	}
	while (start + j < len)
	{
		str[start + j] = 0;
		j++;
	}
}

//del all
char	*single_quotes(char *str, int *i, t_all *all)
{
	int		start;

	(void) all;
	start = *i;
	(*i)++;
	while (str[*i] && str[*i + 1] && str[*i] != '\'')
	{
		if (str[*i] == ' ')
			str[*i] = '\a';
		(*i)++;
	}
	remove_quotes(str, start, i);
	(*i) -= 2;
	return (str);
}

char	*double_quotes(char *str, int *i, t_all *all)
{
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i + 1] && str[*i] != '\"')
	{
		if (str[*i] == '$' && (str[*i + 1] == '_' || \
			ft_isalpha(str[*i + 1])))
		{
			str = env_replace(str, i, all->envp);
			(*i)--;
		}
		if (str[*i] == ' ')
			str[*i] = '\a';
		(*i)++;
	}
	remove_quotes(str, start, i);
	(*i) -= 2;
	return (str);
}
