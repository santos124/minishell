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

char	*save_redir_name(char *str, int *i, t_all *all)
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
	result = ft_substr(str, start, *i - start, all);
	remove_redirect(str, tmp, *i);
	*i = tmp;
	return (result);
}


void	all_redir_list(t_redir *new, t_all *all)
{
	t_redir	*tmp;

	tmp = all->redir;
	if (all->redir == NULL)
	{
		all->redir = new;
		all->redir->cmd = 1;
		if (all->redir->in && all->redir->two)
			all->redir->name = ft_strjoin("heredoc", "1", all);
		if (all->redir->name == NULL)
			ft_exit(12, "malloc", all);
	}
	else
	{
		while (all->redir->all_next != NULL)
			all->redir = all->redir->all_next;
		all->redir->all_next = new;
		all->redir->all_next->cmd = all->num_cmd;
		if (all->redir->all_next->in && all->redir->all_next->two)
			all->redir->all_next->name = ft_strjoin("heredoc", \
				ft_itoa(all->redir->all_next->cmd, all), all);
		if (all->redir->name == NULL)
			ft_exit(12, "malloc", all);
		all->redir = tmp;
	}
}
