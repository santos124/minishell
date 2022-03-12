/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:31:47 by eaurelio          #+#    #+#             */
/*   Updated: 2022/03/12 19:31:51 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *cmd, char **envp)
{
	char	**pre_path;
	char	*full_path;
	char	*path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/') || (cmd[1] == '.'))
		return (cmd);
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	pre_path = ft_split(envp[i] + 5, ':');
	if (!pre_path)
		err_exit(12, "malloc");
	i = 0;
	while (pre_path[i])
	{
		path = ft_strjoin(pre_path[i], "/");
		full_path = ft_strjoin(path, cmd);
		free_null((void **)&path);
		if (!access(full_path, F_OK))
			return (full_path);
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
		err_exit(errno, cmd->in->name);
	file[1] = -2;
	if (cmd->out)
	{
		while (!cmd->out->last)
			cmd->out = cmd->out->next;
		if (cmd->out && cmd->out->doub)
			file[1] = open(cmd->out->name, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (cmd->out && !cmd->out->doub)
			file[1] = open(cmd->out->name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if (file[1] == -1)
		err_exit(errno, cmd->out->name);
	ft_dup2(file, all, cmd, i);
}

static void	fail_execve(t_all *all, char *path, t_cmd *cmd)
{
	if (!path)
	{
		all->errnum = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		err_exit(all->errnum, NULL);
	}
	if (access(path, F_OK))
	{
		all->errnum = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		err_exit(all->errnum, NULL);
	}
	if (path && access(path, X_OK))
	{
		all->errnum = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		err_exit(all->errnum, NULL);
	}
}

void	run_child(int i, t_all *all)
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
		err_exit(run_builtin(cmd, all), NULL);
	valid_path(all, cmd->cmd[0]);
	path = get_path(cmd->cmd[0], all->env);
	if (execve(path, cmd->cmd, all->env) == -1)
		fail_execve(all, path, cmd);
}
