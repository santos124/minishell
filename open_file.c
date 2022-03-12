#include "minishell.h"

static int	open_error(int err_n, char *path_msg, t_all *all)
{
	char	*err_msg;

	if (err_n == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path_msg, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	else if (err_n == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path_msg, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else
	{
		err_msg = strerror(err_n);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path_msg, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	all->errnum = 1;
	return (1);
}

static int	check_env_for_open(t_red *tmp, t_env *env)
{
	if (!(ft_strcmp(env->key, ft_substr(tmp->name, \
		1, ft_strlen(tmp->name)))))
	{
		if (env->val)
		{
			free (tmp->name);
			tmp->name = ft_strdup(env->val);
			return (0);
		}
	}
	return (1);
}

static int	false_red(t_red *tmp, t_all *all)
{
	t_env	*env;

	if (ft_strchr(tmp->name, '/') || tmp->name[1] == '.')
		return (3);
	if (tmp->name[0] != '$')
		return (0);
	env = all->envp;
	while (env)
	{
		if (!check_env_for_open(tmp, env))
			return (0);
		env = env->next;
	}
	return (1);
}

static int	common_open(t_red *tmp, t_all *all)
{
	int	fd;

	if (false_red(tmp, all) != 0)
		return (open_error(false_red(tmp, all), tmp->name, all));
	if (tmp->in)
	{
		fd = open(tmp->name, O_RDWR);
		if (fd == -1)
			return (open_error(errno, tmp->name, all));
	}
	else if (tmp->doub)
	{
		fd = open(tmp->name, O_RDWR | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			return (open_error(errno, tmp->name, all));
	}
	else
	{
		fd = open(tmp->name, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			return (open_error(errno, tmp->name, all));
	}
	close(fd);
	return (0);
}

int	open_file(t_all *all)
{
	t_red	*tmp;

	tmp = all->red;
	while (tmp)
	{
		if (tmp->in && tmp->doub)
			heredoc_open(tmp->name, tmp->limiter, all);
		else
		{
			if (common_open(tmp, all))
				return (1);
		}
		tmp = tmp->all_next;
	}
	return (0);
}
