#include "minishell.h"

void	handler_parent(int sig_num) // +
{
	if (sig_num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay(); // измените то, что отображается на экране, чтобы
		// отразить текущее содержимое файла rl_line_buffer
		ft_putstr_fd("  \b\b\b\b\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1); // Замените содержимое rl_line_buffer текстом
		// Точка и отметка сохраняются, если это возможно. Если значение clear_undo
		// не равно нулю, список отмены, связанный с текущей строкой, очищается
		rl_redisplay();
	}
	else if (sig_num == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 1);
	}
}

void	handler_child(int sig_num) // +
{
	if (sig_num == SIGINT)
		rl_on_new_line();
	else if (sig_num == SIGQUIT)
		ft_putstr_fd("", 1);
}

void	handler_heredoc(int sig) // -
{
	(void)sig;
	write(STDOUT_FILENO, "\b\b  \b\b\n", 7);
	rl_on_new_line();
	err_exit(1, NULL);
}

void	get_line(char **line, t_all *all) // +
{
	signal(SIGINT, &handler_parent); // SIGINT (Ctrl-C) - сигнал, применяемый в
	// POSIX-системах для остановки процесса пользователем с терминала
	signal(SIGQUIT, &handler_parent); // SIGQUIT (Ctrl-\) - сигнал, используемый в
	// POSIX-системах, посылаемый процессу для остановки и указывающий, что система должна выполнить дамп памяти для процесса
	rl_on_new_line(); // cообщите процедурам обновления, что мы перешли на
	// новую (пустую) строку, обычно после вывода новой строки
	*line = readline("minishell: ");
	if (*line && **line)
		add_history(*line); // сохранить строку в списке истории
	else if (*line == NULL) // Ctrl D тут обрабатывается
	{
		printf("exit\n");
		err_exit(all->errnum, NULL);
	}
}
