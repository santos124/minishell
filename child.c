#include "minishell.h"

static char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*path_part;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/') || (cmd[1] == '.'))
		return (cmd);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		err_exit(12, "malloc"); //, all);
	i = 0;
	while (paths[i])
	{
		path_part = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path_part, cmd);
		free_null((void**)&path_part);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

static void	open_dup(int i, t_cmd *cmd, t_all *all)
{
	int	file[2];

	file[0] = -2;
	if (cmd->in)
	{
		while (!cmd->in->last)
			cmd->in = cmd->in->next;
		file[0] = open(cmd->in->name, O_RDONLY);
	}
	if (file[0] == -1)
		err_exit(errno, cmd->in->name); //, all);
	file[1] = -2;
	if (cmd->out)
	{
		while (!cmd->out->last)
			cmd->out = cmd->out->next;
		if (cmd->out && cmd->out->doub)
			file[1] = open(cmd->out->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (cmd->out && !cmd->out->doub)
			file[1] = open(cmd->out->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file[1] == -1)
		err_exit(errno, cmd->out->name); //, all);
	ft_dup2(i, file, cmd, all);
}

void	execve_faild(t_all *all, char *path, t_cmd *cmd)
{
	if (!path)
	{
		all->errnum = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		err_exit(all->errnum, NULL); //, all);
	}
	if (access(path, F_OK) != 0)
	{
		all->errnum = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		write(2, " : No such file or directory\n", 29);
		err_exit(all->errnum, NULL); //, all);
	}
	if (path && access(path, X_OK) != 0)
	{
		all->errnum = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		err_exit(all->errnum, NULL); //, all);
	}
}

void	child_action(int i, t_all *all)
{
	t_cmd		*cmd;
	char		*path;
	int			num;
	
	num = 0;
	cmd = all->cmd;
	while (num < i)
	{
		cmd = cmd->next;
		num++;
	}
	if (!cmd->cmd || !cmd->cmd[0])
		exit(0);
	open_dup(i, cmd, all);
	if (cmd->id_cmd)
		err_exit(run_builtin(cmd, all), NULL); //, all);
	valid_path(all, cmd->cmd[0]);
	path = get_path(cmd->cmd[0], all->env);
	if (execve(path, cmd->cmd, all->env) == -1)
		execve_faild(all, path, cmd);
}
