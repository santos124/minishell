#include "minishell.h"

static void	sub_gns(char **last, char **str) // +
{
	*str = ft_strdup("\0");
	*last = ft_strdup("\0\0");
	if (!*str)
		err_exit(12, "malloc");
	if (!*last)
		err_exit(12, "malloc");
}

static void	get_next_str(char **str) // +
{
	char	*last;
	char	*tmp;

	sub_gns(&last, str);
	while (*last != '\n')
	{
		read(0, last, 1);
		if (*last == '\n')
			break ;
		if (!*last)
		{
			*str = NULL;
			return ;
		}
		tmp = ft_strjoin(*str, last);
		if (!tmp)
		{
			free_null((void**)&last);
			err_exit(12, "malloc");
		}
		free_null((void**)&*str);
		*str = tmp;
	}
	free_null((void**)&last);
}

static void	ft_waitpid(pid_t pid, int status, t_all *all) // +
{
	waitpid(pid, &status, 0);
	if (all)
	{
		if (WIFEXITED(status))
			all->errnum = WEXITSTATUS(status);
		else
			all->errnum = 1;
	}
}

static void	sub_heredoc(char *name, char *limiter, int fd) //+
{
	char	*str;

	while (1)
	{
		ft_putstr_fd(">", 1);
		signal(SIGINT, &handler_heredoc);
		get_next_str(&str);
		if (!str)
		{
			ft_putstr_fd("  \b\b", 1);
			break ;
		}		
		if (ft_strcmp(str, limiter))
		{
			if (write(fd, str, ft_strlen(str)) == -1)
				err_exit(errno, name);
			if (write(fd, "\n", 1) == -1)
				err_exit(errno, name);
		}
		else
			break ;
		free_null((void**)&str);
	}
}

void	heredoc_open(char *name, char *limiter, t_all *all) // +
{
	pid_t	pid;
	int		fd;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		all->errnum = errno;
		waitpid(pid, &status, 0);
		err_exit(all->errnum, "fork");
	}
	if (pid != 0)
		signal(SIGINT, SIG_IGN); // SIG_IGN - функция, которая игнорирует
	// сигнал кроме сигналов sigkill и sigstop
	if (pid == 0)
	{
		fd = open(name, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0777);
		if (fd == -1)
			err_exit(errno, name);
		sub_heredoc(name, limiter, fd);
		close(fd);
		err_exit(all->errnum, NULL);
	}
	ft_waitpid(pid, status, all);
	signal(SIGINT, &handler_parent);
}