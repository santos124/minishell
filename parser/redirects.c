#include "../minishell.h"

void	new_in_redir(char *str, int *i, t_red *new)
{
	if (str[*i + 1] && str[*i + 1] != '<')
	{
		new->name = name_red(str, i);
		new->limiter = NULL;
		new->doub = 0;
		new->in = 1;
	}
	else if (str[*i + 1] && str[*i + 1] == '<')
	{
		new->limiter = ft_strtrim(ft_strtrim(name_red(str, i), "'"), "\"");
		new->name = ft_strdup("heredoc"); //, all);
		new->doub = 1;
		new->in = 1;
	}
}

t_red	*new_red(char *str, int *i, t_all *all)
{
	t_red	*new;

	new = (t_red *)malloc(sizeof(t_red));
	if (str[*i + 1] && str[*i] == '>' && str[*i + 1] != '>')
	{
		new->name = name_red(str, i);
		new->limiter = NULL;
		new->doub = 0;
		new->in = 0;
	}
	else if (str[*i + 1] && str[*i] == '>' && str[*i + 1] == '>')
	{
		new->name = name_red(str, i);
		new->limiter = NULL;
		new->doub = 1;
		new->in = 0;
	}
	else if (str[*i] && str[*i] == '<')
		new_in_redir(str, i, new);
	new->next = NULL;
	new->all_next = NULL;
	list_reds(new, all);
	return (new);
}

void	add_in_redir(char *str, int *i, t_cmd *cmd, t_all *all)
{
	t_red	*tmp;

	tmp = cmd->in;
	if (cmd->in == NULL)
	{
		cmd->in = new_red(str, i, all);
		cmd->in->last = 1;
	}
	else
	{
		while (cmd->in->next)
			cmd->in = cmd->in->next;
		cmd->in->next = new_red(str, i, all);
		cmd->in->next->last = 1;
		cmd->in->last = 0;
		cmd->in = tmp;
	}
}

void	add_out_red(char *str, int *i, t_cmd *cmd, t_all *all)
{
	t_red	*tmp;

	tmp = cmd->out;
	if (cmd->out == NULL)
	{
		cmd->out = new_red(str, i, all);
		cmd->out->last = 1;
	}
	else
	{
		while (cmd->out->next)
			cmd->out = cmd->out->next;
		cmd->out->next = new_red(str, i, all);
		cmd->out->next->last = 1;
		cmd->out->last = 0;
		cmd->out = tmp;
	}
}

char	*parsing_reds(char *str, int *i, t_cmd *cmd, t_all *all)
{
	if (str[*i] && str[*i] == '>')
		add_out_red(str, i, cmd, all);
	else if (str[*i] && str[*i] == '<')
		add_in_redir(str, i, cmd, all);
	return (str);
}
