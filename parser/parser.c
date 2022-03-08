#include "../minishell.h"

t_cmd	*new_command(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->in = 0;
	new->out = 0;
	new->next = 0;
	new->cmd = 0;
	new->id_cmd = 0;
	return (new);
}

void	parse_line_loop(char **str, t_all *all, t_cmd *cmd, int *i)
{
	while ((*str)[*i] != 0 && (*str)[*i] != '|')
	{		
		while ((*str)[*i] == ' ')
			(*i)++;
		if ((*str)[*i] == '\"')
			(*str) = doub_qts((*str), i, all);
		else if ((*str)[*i] == '\'')
			(*str) = single_qts((*str), i, all);
		if ((*str)[*i] == '$' && ((*str)[*i + 1] == '_' || \
			ft_isalpha((*str)[*i + 1])))
			(*str) = replace_env((*str), i, all->envp);
		if ((*str)[*i] == '$' && (*str)[*i + 1] == '?')
			(*str) = get_last_exit_code((*str), all, i);
		if (((*str)[*i] == '>' || (*str)[*i] == '<') && (*str)[(*i) + 1])
			(*str) = parsing_reds((*str), i, cmd, all);
		if ((*str)[*i] != '|')
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
	j = 0;
	while (cmd[i] != 0)
	{
		j = 0;
		while (cmd[i][j] != 0)
		{
			if (cmd[i][j] == '\a')
				cmd[i][j] = ' ';
			j++;
		}
		i++;
	}
}

char	*parse_line(char **str, t_all *all, t_cmd *cmd)
{
	char	*one_cmd;
	int		i;
	int		start;
	char	*new_str;

	i = 0;
	start = 0;
	if ((*str)[i] == '|')
	{
		start++;
		i++;
	}
	parse_line_loop(str, all, cmd, &i);
	if ((*str)[i] == '|')
		one_cmd = ft_substr(*str, start, i - 1);
	else
		one_cmd = ft_substr(*str, start, i);
	cmd->cmd = ft_split(one_cmd, ' ');
	replace_spaces(cmd->cmd);
	free(one_cmd);
	new_str = ft_strdup(&((*str)[i])); //, all);
	free(*str);
	return (new_str);
}

int	parser(t_all *all, char *str)
{
	t_cmd	*tmp;

	if (!str)
		err_exit(12, "malloc"); //, all);
	format_blanks(&str);
	if (parse_check_err(str, all))
		return (1);
	all->cmd = new_command();
	all->num_cmd = 1;
	tmp = all->cmd;
	str = parse_line(&str, all, all->cmd);
	if (!str)
		err_exit(12, "malloc"); //, all);
	while (str[0] && str[0] == '|')
	{
		all->cmd->next = new_command();
		all->cmd = all->cmd->next;
		all->num_cmd++;
		str = parse_line(&str, all, all->cmd);
		if (!str)
			err_exit(12, "malloc"); //, all);
	}
	all->cmd = tmp;
	free(str);
	return (0);
}
