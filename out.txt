#include "minishell.h"

void	set_built(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->cmd[0])
		{
			if (!ft_strcmp(cmd->cmd[0], "echo"))
				cmd->built = 1;
			else if (!ft_strcmp(cmd->cmd[0], "cd"))
				cmd->built = 2;
			else if (!ft_strcmp(cmd->cmd[0], "pwd"))
				cmd->built = 3;
			else if (!ft_strcmp(cmd->cmd[0], "export"))
				cmd->built = 4;
			else if (!ft_strcmp(cmd->cmd[0], "unset"))
				cmd->built = 5;
			else if (!ft_strcmp(cmd->cmd[0], "env"))
				cmd->built = 6;
			else if (!ft_strcmp(cmd->cmd[0], "exit"))
				cmd->built = 7;
		}
		cmd = cmd->next;
	}
}

int	run_built(t_command *cmd, t_all *all)
{
	if (cmd->built == 1)
		return (ft_echo(all, cmd));
	if (cmd->built == 2)
		return (ft_cd(all, cmd));
	if (cmd->built == 3)
		return (ft_pwd(all));
	if (cmd->built == 4)
		return (ft_export(all, cmd));
	if (cmd->built == 5)
		return (ft_unset(cmd, all));
	if (cmd->built == 6)
		return (ft_env(all, cmd));
	if (cmd->built == 7)
		return (ft_exit_cmd(all, cmd));
	return (0);
}

void	execution(t_all *all)
{
	int	fd;

	fd = 0;
	set_built(all->cmd);
	ft_env_list_to_array(all->envp, all);
	if (!check_open(all))
	{
		all->num = ft_count_cmd(all->cmd);
		if (all->num == 0)
			return ;
		if (all->num > 1)
		{
			ft_pipe(all);
		}
		if (all->num == 1 && all->cmd->built)
		{
			fd = dup_cmd(all->cmd, all);
			all->errnum = run_built(all->cmd, all);
			redup_cmd(fd, all);
		}
		else if (all->num != 1 || all->cmd->cmd[0])
			pipex(all);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_all	*all;
	char	*line;

	(void)argv;
	ft_init_structs(&all);
	if (argc != 1)
		ft_exit(1, NULL, all);
	parse_env(env, all);
	ft_shlvl_check(all);
	while (1)
	{
		go_readline(&line, all);
		if (parser(all, line) == 0)
		{
			execution(all);
			free_structs(all);
		}
	}
	return (0);
}
