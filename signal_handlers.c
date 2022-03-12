/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:34:57 by eaurelio          #+#    #+#             */
/*   Updated: 2022/03/12 19:34:59 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_parent(int sig_num)
{
	if (sig_num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b\b\b\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (sig_num == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 1);
	}
}

void	handler_child(int sig_num)
{
	if (sig_num == SIGINT)
		rl_on_new_line();
	else if (sig_num == SIGQUIT)
		ft_putstr_fd("", 1);
}

void	handler_heredoc(int sig)
{
	(void)sig;
	ft_putstr_fd("\b\b  \b\b\n", 1);
	rl_on_new_line();
	err_exit(1, NULL);
}

void	get_line(char **line, t_all *all)
{
	signal(SIGINT, &handler_parent);
	signal(SIGQUIT, &handler_parent);
	rl_on_new_line();
	*line = readline("minishell: ");
	if (*line && **line)
		add_history(*line);
	else if (*line == NULL)
	{
		printf("exit\n");
		err_exit(all->errnum, NULL);
	}
}
