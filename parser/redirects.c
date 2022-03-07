#include "../minishell.h"

void	new_in_redir(char *str, int *i, t_redir *new, t_all *all)
{
	if (str[*i + 1] && str[*i + 1] != '<')
	{
		new->name = save_redir_name(str, i, all);
		new->limiter = NULL;
		new->two = 0;
		new->in = 1;
	}
	else if (str[*i + 1] && str[*i + 1] == '<')
	{
		new->limiter = save_redir_name(line, i, all);
		new->name = ft_strdup("heredoc"); //, all);
		new->two = 1;
		new->in = 1;
	}
}

t_redir	*new_redir(char *str, int *i, t_all *all)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (str[*i + 1] && str[*i] == '>' && str[*i + 1] != '>')
	{
		new->name = save_redir_name(str, i, all);
		new->limiter = NULL;
		new->two = 0;
		new->in = 0;
	}
	else if (str[*i + 1] && str[*i] == '>' && str[*i + 1] == '>')
	{
		new->name = save_redir_name(str, i, all);
		new->limiter = NULL;
		new->two = 1;
		new->in = 0;
	}
	else if (str[*i] && str[*i] == '<')
		new_in_redir(str, i, new, all);
	new->next = NULL;
	new->all_next = NULL;
	all_redir_list(new, all);
	return (new);
}

void	add_in_redir(char *str, int *i, t_command *cmd, t_all *all)
{
	t_redir	*tmp;

	tmp = cmd->in;
	if (cmd->in == NULL)
	{
		cmd->in = new_redir(str, i, all);
		cmd->in->target = 1;
	}
	else
	{
		while (cmd->in->next)
			cmd->in = cmd->in->next;
		cmd->in->next = new_redir(str, i, all);
		cmd->in->next->target = 1;
		cmd->in->target = 0;
		cmd->in = tmp;
	}
}

void	add_out_redir(char *str, int *i, t_command *cmd, t_all *all)
{
	t_redir	*tmp;

	tmp = cmd->out;
	if (cmd->out == NULL)
	{
		cmd->out = new_redir(str, i, all);
		cmd->out->target = 1;
	}
	else
	{
		while (cmd->out->next)
			cmd->out = cmd->out->next;
		cmd->out->next = new_redir(str, i, all);
		cmd->out->next->target = 1;
		cmd->out->target = 0;
		cmd->out = tmp;
	}
}

char	*parse_redirects(char *str, int *i, t_command *cmd, t_all *all)
{
	if (str[*i] && str[*i] == '>')
		add_out_redir(str, i, cmd, all);
	else if (str[*i] && str[*i] == '<')
		add_in_redir(str, i, cmd, all);
	return (str);
}
