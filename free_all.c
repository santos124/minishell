#include "minishell.h"

void	free_redir_env_fd(t_all *all)
{
	int		i;
	t_red	*redir_temp;

	while (all->red)
	{
		redir_temp = all->red->all_next;
		if (all->red->in && all->red->doub)
		{
			unlink(all->red->name);
			free(all->red->limiter);
		}
		free(all->red->name);
		free(all->red);
		all->red = redir_temp;
	}
	i = 0;
	while (all->env[i])
	{
		free(all->env[i]);
		i++;
	}
	free (all->env);
	if (all->num > 1)
		free(all->fd);
}

void	free_commands(t_all *all)
{
	int	i;

	i = 0;
	if (all->cmd->cmd && all->cmd->cmd[0] && \
		ft_strcmp(all->cmd->cmd[0], "cd") == 0 && \
		ft_strcmp(all->cmd->cmd[1], "~") == 0)
	{
		free(all->cmd->cmd[0]);
		free(all->cmd->cmd[1]);
	}
	else
	{
		while (all->cmd->cmd[i])
		{
			free(all->cmd->cmd[i]);
			i++;
		}
	}
}

void	free_struct(t_all *all)
{
	t_cmd	*cmd_temp;

	while (all->cmd)
	{
		cmd_temp = all->cmd->next;
		free_commands(all);
		free(all->cmd->cmd);
		free(all->cmd);
		all->cmd = cmd_temp;
	}
	free_redir_env_fd(all);
}
