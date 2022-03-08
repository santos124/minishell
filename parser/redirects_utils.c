#include "../minishell.h"

void	remove_redirect(char *str, int start, int end)
{
	int	len;
	int	i;

	len = end - start;
	i = 0;
	while (str[end + i])
	{
		str[start + i] = str[end + i];
		i++;
	}
	str[start + i] = 0;
	while (str[start + i + 1])
	{
		str[start + i + 1] = 0;
		i++;
	}
}

char	*name_red(char *str, int *i)
{
	char	*result;
	int		count;
	int		start;
	int		tmp;

	count = 0;
	tmp = *i;
	while (str[*i] && (str[*i] == '>' || str[*i] == '<'))
		(*i)++;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '|')
		(*i)++;
	result = ft_substr(str, start, *i - start);
	remove_redirect(str, tmp, *i);
	*i = tmp;
	return (result);
}


void	list_reds(t_red *new, t_all *all)
{
	t_red	*tmp;

	tmp = all->red;
	if (all->red == NULL)
	{
		all->red = new;
		all->red->cmd = 1;
		if (all->red->in && all->red->doub)
			all->red->name = ft_strjoin("heredoc", "1");
		if (all->red->name == NULL)
			err_exit(12, "malloc"); //, all);
	}
	else
	{
		while (all->red->all_next != NULL)
			all->red = all->red->all_next;
		all->red->all_next = new;
		all->red->all_next->cmd = all->num_cmd;
		if (all->red->all_next->in && all->red->all_next->doub)
			all->red->all_next->name = ft_strjoin("heredoc", \
				ft_itoa(all->red->all_next->cmd));
		if (all->red->name == NULL)
			err_exit(12, "malloc"); //, all);
		all->red = tmp;
	}
}
