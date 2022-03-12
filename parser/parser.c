/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:36:08 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:36:10 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*new_command(void)
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

static void	replace_spaces(char **cmd)
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

static void	parse_line_loop(char **str, t_all *all, t_cmd *cmd, int *i)
{
	while ((*str)[*i] != 0 && (*str)[*i] != '|')
	{		
		while ((*str)[*i] == ' ')
			(*i)++;
		if ((*str)[*i] == '\"')
			(*str) = doub_qts((*str), i, all);
		else if ((*str)[*i] == '\'')
			(*str) = single_qts((*str), i);
		if ((*str)[*i] == '$' && ((*str)[*i + 1] == '_' || \
			ft_isalpha((*str)[*i + 1])))
			(*str) = replace_var((*str), i, all->envp);
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

static char	*parse_line(char **str, t_all *all, t_cmd *cmd)
{
	char	*one_cmd;
	char	*new_str;
	int		start;
	int		i;

	start = 0;
	i = 0;
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
	free_null((void **)&one_cmd);
	new_str = ft_strdup(&((*str)[i]));
	free_null((void **)&*str);
	return (new_str);
}

int	parser(t_all *all, char *str)
{
	t_cmd	*tmp;

	if (!str)
		err_exit(12, "malloc");
	format_blanks(&str);
	if (parse_check_err(str, all))
		return (1);
	all->cmd = new_command();
	all->num_cmd = 1;
	tmp = all->cmd;
	str = parse_line(&str, all, all->cmd);
	if (!str)
		err_exit(12, "malloc");
	while (str[0] && str[0] == '|')
	{
		all->cmd->next = new_command();
		all->cmd = all->cmd->next;
		all->num_cmd++;
		str = parse_line(&str, all, all->cmd);
		if (!str)
			err_exit(12, "malloc");
	}
	all->cmd = tmp;
	free_null((void **)&str);
	return (0);
}
