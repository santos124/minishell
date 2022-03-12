#include "minishell.h"

static void	free_redir_env_fd(t_all *all)
{
	t_red	*red_tmp;
	int		i;

	while (all && all->red)
	{
		red_tmp = all->red->all_next;
		if (all->red->in && all->red->doub)
		{
			unlink(all->red->name);
			free_null((void**)&all->red->limiter);
		}
		free_null((void**)&all->red->name);
		free_null((void**)&all->red);
		all->red = red_tmp;
	}
	i = 0;
	while (all && all->env[i])
	{
		free_null((void**)&all->env[i]);
		i++;
	}
	free_null((void**)&all->env);
	if (all->num > 1)
		free_null((void**)&all->fd);
}

static void	free_commands(t_all *all)
{
	int	i;

	i = 0;
	if (all && all->cmd->cmd && all->cmd->cmd[0] && \
		ft_strcmp(all->cmd->cmd[0], "cd") == 0 && \
		ft_strcmp(all->cmd->cmd[1], "~") == 0)
	{
		free_null((void**)&all->cmd->cmd[0]);
		free_null((void**)&all->cmd->cmd[1]);
	}
	else
	{
		while (all && all->cmd->cmd[i])
		{
			free_null((void**)&all->cmd->cmd[i]);
			i++;
		}
	}
}

void	free_struct(t_all *all)
{
	t_cmd	*cmd_tmp;

	while (all && all->cmd)
	{
		cmd_tmp = all->cmd->next;
		free_commands(all);
		free_null((void**)&all->cmd->cmd);
		free_null((void**)&all->cmd);
		all->cmd = cmd_tmp;
	}
	free_redir_env_fd(all);
}
