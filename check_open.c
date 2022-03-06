#include "minishell.h"

static int	err_open(int errnum, char *msg, t_all *all)
{
	char	*errmsg;

	if (errnum == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	else if (errnum == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		errmsg = strerror(errnum);
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
		write(2, errmsg, ft_strlen(errmsg));
		write(2, "\n", 1);
	}
	all->errnum = 1;
	return (1);
}

int	ambiguous_redirect(t_redir *tmp, t_all *all)
{
	t_env	*env;

	if (ft_strchr(tmp->name, '/') || (tmp->name[1] == '.'))
		return (3);
	if (tmp->name[0] != '$')
		return (0);
	env = all->envp;
	while (env)
	{
		if (!(ft_strcmp(env->key, ft_substr(tmp->name, \
		1, ft_strlen(tmp->name), all))))
		{
			if (env->value)
			{
				free (tmp->name);
				tmp->name = ft_strdup(env->value, all);
				return (0);
			}
		}
		env = env->next;
	}
	return (1);
}

static int	open_file(t_redir *tmp, t_all *all)
{
	int	fd;

	if (ambiguous_redirect(tmp, all) != 0)
		return (err_open(ambiguous_redirect(tmp, all), tmp->name, all));
	if (!tmp->in && tmp->two) // исходящий И 2
	{
		fd = open(tmp->name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (err_open(errno, tmp->name, all));
	}
	else if (!tmp->in && !tmp->two) // исходящий И 1
	{
		fd = open(tmp->name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (err_open(errno, tmp->name, all));
	}
	else //в осталтных
	{
		fd = open(tmp->name, O_RDWR);
		if (fd == -1)
			return (err_open(errno, tmp->name, all));
	}
	close(fd);
	return (0);
}

int	check_open(t_all *all)
{
	t_redir	*tmp;

	tmp = all->redir;
	while (tmp)
	{
		if (!tmp->in || !tmp->two) //не входящий ИЛИ не двойной
		{
			if (open_file(tmp, all))
				return (1);
		}
		else
			heredoc(tmp->name, tmp->limiter, all);
		tmp = tmp->all_next;
	}
	return (0);
}
