#include "../minishell.h"

t_command	*new_command(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
	new->cmd = NULL;
	new->built = 0;
	return (new);
}

void	parse_line_loop(char **line, t_all *all, t_command *cmd, int *i)
{
	while ((*line)[*i] && (*line)[*i] != '|')
	{		
		while ((*line)[*i] == ' ')
			(*i)++;
		if ((*line)[*i] == '\"')
			(*line) = double_quotes((*line), i, all);
		else if ((*line)[*i] == '\'')
			(*line) = single_quotes((*line), i, all);
		if ((*line)[*i] == '$' && ((*line)[*i + 1] == '_' || \
			ft_isalpha((*line)[*i + 1])))
			(*line) = env_replace((*line), i, all->envp, all);
		if ((*line)[*i] == '$' && (*line)[*i + 1] == '?')
			(*line) = exit_code_replace((*line), all, i);
		if (((*line)[*i] == '>' || (*line)[*i] == '<') && (*line)[(*i) + 1])
			(*line) = parse_redirects((*line), i, cmd, all);
		if ((*line)[*i] != '|')
			(*i)++;
		else
			all->num_cmd++;
	}
}

void	replace_spaces(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\a')
				cmd[i][j] = ' ';
			j++;
		}
		i++;
	}
}

char	*parse_line(char **line, t_all *all, t_command *cmd)
{
	char	*one_cmd;
	int		i;
	int		start;
	char	*new_line;

	i = 0;
	start = 0;
	if ((*line)[i] == '|')
	{
		i++;
		start++;
	}
	parse_line_loop(line, all, cmd, &i);
	if ((*line)[i] == '|')
		one_cmd = ft_substr(*line, start, i - 1, all);
	else
		one_cmd = ft_substr(*line, start, i, all);
	cmd->cmd = ft_split(one_cmd, ' ', all);
	replace_spaces(cmd->cmd);
	free(one_cmd);
	new_line = ft_strdup(&(*line)[i], all);
	free(*line);
	return (new_line);
}

/* return 1 if syntax error */
int	parser(t_all *all, char *line)
{
	t_command	*temp;

	if (!line)
		ft_exit(12, "malloc", all);
	tabs_to_spaces(&line);
	if (check_syntax(line, all))
		return (1);
	all->cmd = new_command();
	all->num_cmd = 1;
	temp = all->cmd;
	line = parse_line(&line, all, all->cmd);
	if (!line)
		ft_exit(12, "malloc", all);
	while (line[0] && line[0] == '|')
	{
		all->cmd->next = new_command();
		all->cmd = all->cmd->next;
		all->num_cmd++;
		line = parse_line(&line, all, all->cmd);
		if (!line)
			ft_exit(12, "malloc", all);
	}
	all->cmd = temp;
	free(line);
	return (0);
}
