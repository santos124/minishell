#include "../minishell.h"

void	remove_redirect(char *line, int start, int end)
{
	int	len;
	int	i;

	len = end - start;
	i = 0;
	(void)line;
	while (line[end + i])
	{
		line[start + i] = line[end + i];
		i++;
	}
	line[start + i] = '\0';
	while (line[start + i + 1])
	{
		line[start + i + 1] = '\0';
		i++;
	}
}

char	*save_redir_name(char *line, int *i, t_all *all)
{
	int		begin;
	int		save;
	int		count;
	char	*result;

	save = *i;
	count = 0;
	while (line[*i] && (line[*i] == '>' || line[*i] == '<'))
		(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	begin = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '|')
		(*i)++;
	result = ft_substr(line, begin, *i - begin, all);
	remove_redirect(line, save, *i);
	*i = save;
	return (result);
}

void	all_redir_list(t_redir *new, t_all *all)
{
	t_redir	*temp;

	temp = all->redir;
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
		while (all->redir->all_next)
			all->redir = all->redir->all_next;
		all->redir->all_next = new;
		all->redir->all_next->cmd = all->num_cmd;
		if (all->redir->all_next->in && all->redir->all_next->two)
			all->redir->all_next->name = ft_strjoin("heredoc", \
				ft_itoa(all->redir->all_next->cmd, all), all);
		if (all->redir->name == NULL)
			ft_exit(12, "malloc", all);
		all->redir = temp;
	}
}
