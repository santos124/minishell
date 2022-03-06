#include "../minishell.h"

void	new_in_redir(char *line, int *i, t_redir *new, t_all *all)
{
	if (line[*i + 1] && line[*i + 1] != '<')
	{
		new->name = save_redir_name(line, i, all);
		new->two = 0;
		new->in = 1;
		new->limiter = NULL;
	}
	else if (line[*i + 1] && line[*i + 1] == '<')
	{
		new->limiter = save_redir_name(line, i, all);
		new->name = ft_strdup("heredoc", all);
		new->two = 1;
		new->in = 1;
	}
}

t_redir	*new_redir(char *line, int *i, t_all *all)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (line[*i + 1] && line[*i] == '>' && line[*i + 1] != '>')
	{
		new->name = save_redir_name(line, i, all);
		new->two = 0;
		new->in = 0;
		new->limiter = NULL;
	}
	else if (line[*i + 1] && line[*i] == '>' && line[*i + 1] == '>')
	{
		new->name = save_redir_name(line, i, all);
		new->two = 1;
		new->in = 0;
		new->limiter = NULL;
	}
	else if (line[*i] && line[*i] == '<')
	{
		new_in_redir(line, i, new, all);
	}
	new->next = NULL;
	new->all_next = NULL;
	all_redir_list(new, all);
	return (new);
}

void	add_in_redir(char *line, int *i, t_command *cmd, t_all *all)
{
	t_redir	*temp;

	temp = cmd->in;
	if (cmd->in == NULL)
	{
		cmd->in = new_redir(line, i, all);
		cmd->in->target = 1;
	}
	else
	{
		while (cmd->in->next)
			cmd->in = cmd->in->next;
		cmd->in->next = new_redir(line, i, all);
		cmd->in->next->target = 1;
		cmd->in->target = 0;
		cmd->in = temp;
	}
}

void	add_out_redir(char *line, int *i, t_command *cmd, t_all *all)
{
	t_redir	*temp;

	temp = cmd->out;
	if (cmd->out == NULL)
	{
		cmd->out = new_redir(line, i, all);
		cmd->out->target = 1;
	}
	else
	{
		while (cmd->out->next)
			cmd->out = cmd->out->next;
		cmd->out->next = new_redir(line, i, all);
		cmd->out->next->target = 1;
		cmd->out->target = 0;
		cmd->out = temp;
	}
}

char	*parse_redirects(char *line, int *i, t_command *cmd, t_all *all)
{
	if (line[*i] && line[*i] == '>')
		add_out_redir(line, i, cmd, all);
	else if (line[*i] && line[*i] == '<')
		add_in_redir(line, i, cmd, all);
	return (line);
}
