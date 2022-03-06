#include "minishell.h"

void	go_readline(char **line, t_all *all)
{
	signal(SIGINT, &sig_handler_parent);
	signal(SIGQUIT, &sig_handler_parent);
	rl_on_new_line();
	*line = readline("minishell>>> ");
	if (*line && **line)
		add_history(*line);
	else if (*line == NULL)
	{
		printf("\033[1Aminishell>>> exit\n");
		ft_exit(all->errnum, NULL, all);
	}
}

void	sig_handler_child(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
	}
	else if (sig_num == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
	}
}

void	sig_handler_parent(int sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (sig_num == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
}

void	heredoc_sig_int(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\b\b  \b\b\n", 7);
	rl_on_new_line();
	ft_exit(1, NULL, NULL);
}
