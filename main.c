#include "minishell.h"

static t_all	*init_struct(t_all *all)
{
	all = (t_all *)malloc(sizeof (t_all));
	if (!all)
		err_exit(12, "malloc");
	all->envp = NULL;
	all->red = NULL;
	all->cmd = NULL;
	all->fd = NULL;
	all->num_cmd = 0;
	all->errnum = 0;
	all->num = 0;
	return (all);
}

static void	set_builtin(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->cmd[0])
		{
			if (!ft_strcmp(cmd->cmd[0], "echo"))
				cmd->id_cmd = 1;
			else if (!ft_strcmp(cmd->cmd[0], "cd"))
				cmd->id_cmd = 2;
			else if (!ft_strcmp(cmd->cmd[0], "pwd"))
				cmd->id_cmd = 3;
			else if (!ft_strcmp(cmd->cmd[0], "export"))
				cmd->id_cmd = 4;
			else if (!ft_strcmp(cmd->cmd[0], "unset"))
				cmd->id_cmd = 5;
			else if (!ft_strcmp(cmd->cmd[0], "env"))
				cmd->id_cmd = 6;
			else if (!ft_strcmp(cmd->cmd[0], "exit"))
				cmd->id_cmd = 7;
		}
		cmd = cmd->next;
	}
}

int	run_builtin(t_cmd *cmd, t_all *all)
{
	if (cmd->id_cmd == 1)
		return (ft_echo(cmd));
	if (cmd->id_cmd == 2)
		return (ft_cd(all, cmd));
	if (cmd->id_cmd == 3)
		return (ft_pwd(all));
	if (cmd->id_cmd == 4)
		return (ft_export(all, cmd));
	if (cmd->id_cmd == 5)
		return (ft_unset(cmd, all));
	if (cmd->id_cmd == 6)
		return (ft_env(all, cmd));
	if (cmd->id_cmd == 7)
		return (ft_exit(all, cmd));
	return (0);
}

static void	run_minishell(t_all *all)
{
	int	fd;

	fd = 0;
	set_builtin(all->cmd);
	env_to_arr(all->envp, all);
	if (!open_file(all))
	{
		all->num = count_cmd(all->cmd);
		if (all->num > 1)
			ft_pipe(all);
		if (all->num == 1 && all->cmd->id_cmd)
		{
			fd = dup_cmd(all->cmd);
			all->errnum = run_builtin(all->cmd, all);
			redup_cmd(fd);
		}
		else if (all->num > 1 || (all->num && all->cmd->cmd[0]))
			pipex(all);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_all	*all;
	char	*str;

	(void)argv;
	all = NULL;
	all = init_struct(all);
	if (argc != 1)
		err_exit(1, NULL);
	parse_env(env, all);
	shlvl_check(all);
	while (1)
	{
		get_line(&str, all);
		if (!parser(all, str))
		{
			run_minishell(all);
			free_struct(all);
		}
	}
	return (0);
}
