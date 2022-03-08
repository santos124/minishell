#include "minishell.h"

static void	gnl_init_strings(char **end, char **line) //, t_all *all)
{
	*line = ft_strdup("\0"); //, all);
	*end = ft_strdup("\0\0"); //, all);
	if (!*line || !*end)
		err_exit(12, "malloc"); //, all);
}

static void	gnl(char **line)
{
	char	*end;
	char	*tmp;

	gnl_init_strings(&end, line); //, all);
	while (*end != '\n')
	{
		read(0, end, 1);
		if (*end == '\n')
			break ;
		if (!*end)
		{
			*line = NULL;
			return ;
		}
		tmp = ft_strjoin(*line, end);
		if (!tmp)
		{
			free(end);
			err_exit(12, "malloc"); //, all);
		}
		free(*line);
		*line = tmp;
	}
	free(end);
}

void	heredoc_loop(char *name, char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		signal(SIGINT, &handler_heredoc);
		gnl(&line);
		if (!line)
		{
			write(1, "  \b\b", 1);
			break ;
		}
		if (ft_strcmp(line, limiter))
		{
			if (write(fd, line, ft_strlen(line)) == -1)
				err_exit(errno, name); //, all);
			if (write(fd, "\n", 1) == -1)
				err_exit(errno, name); //, all);
		}
		else
			break ;
		free(line);
	}
}

static void	ft_waitpid(pid_t pid, int status, t_all *all)
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

void	heredoc_open(char *name, char *limiter, t_all *all)
{
	int		fd;
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		all->errnum = errno;
		waitpid(pid, &status, 0);
		err_exit(all->errnum, "fork"); //, all);
	}
	if (pid != 0)
		signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		fd = open(name, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
		if (fd == -1)
			err_exit(errno, name); //, all);
		heredoc_loop(name, limiter, fd);
		close(fd);
		err_exit(all->errnum, NULL); //, all);
	}
	ft_waitpid(pid, status, all);
	signal(SIGINT, &handler_parent);
}
