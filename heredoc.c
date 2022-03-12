#include "minishell.h"

static void	gnl_init_strings(char **end, char **str) //, t_all *all)
{
	*str = ft_strdup("\0");
	*end = ft_strdup("\0\0");
	if (!*str || !*end)
		err_exit(12, "malloc");
}

static void	get_next_str(char **str)
{
	char	*end;
	char	*tmp;

	gnl_init_strings(&end, str);
	while (*end != '\n')
	{
		read(0, end, 1);
		if (*end == '\n')
			break ;
		if (!*end)
		{
			*str = NULL;
			return ;
		}
		tmp = ft_strjoin(*str, end);
		if (!tmp)
		{
			free_null((void**)&end);
			err_exit(12, "malloc"); //, all);
		}
		free_null((void**)&*str);
		*str = tmp;
	}
	free_null((void**)&end);
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

void	heredoc_loop(char *name, char *limiter, int fd)
{
	char	*str;

	while (1)
	{
		f(1, "> ", 2);
		signal(SIGINT, &handler_heredoc);
		get_next_str(&str);
		if (!str)
		{
			write(1, "  \b\b", 1);
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

void	heredoc_open(char *name, char *limiter, t_all *all)
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
			err_exit(errno, name); //, all);
		heredoc_loop(name, limiter, fd);
		close(fd);
		err_exit(all->errnum, NULL); //, all);
	}
	ft_waitpid(pid, status, all);
	signal(SIGINT, &handler_parent);
}
