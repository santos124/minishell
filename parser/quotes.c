#include "../minishell.h"

void	remove_quotes(char *line, int begin, int *i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(line);
	while (begin + j < *i - 1)
	{
		line[begin + j] = line[begin + j + 1];
		j++;
	}
	while (begin + j < len - 2)
	{
		line[begin + j] = line[begin + j + 2];
		j++;
	}
	while (begin + j < len)
	{
		line[begin + j] = '\0';
		j++;
	}
}

char	*single_quotes(char *line, int *i, t_all *all)
{
	int		begin;

	(void) all;
	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\'')
	{
		if (line[*i] == ' ')
			line[*i] = '\a';
		(*i)++;
	}
	remove_quotes(line, begin, i);
	(*i) -= 2;
	return (line);
}

char	*double_quotes(char *line, int *i, t_all *all)
{
	int		begin;

	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\"')
	{
		if (line[*i] == '$' && (line[*i + 1] == '_' || \
			ft_isalpha(line[*i + 1])))
		{
			line = env_replace(line, i, all->envp, all);
			(*i)--;
		}
		if (line[*i] == ' ')
			line[*i] = '\a';
		(*i)++;
	}
	remove_quotes(line, begin, i);
	(*i) -= 2;
	return (line);
}
